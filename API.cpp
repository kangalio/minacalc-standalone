#include "MinaCalc/MinaCalc.h"

extern "C" {
	#include "API.h"

	// internal utility function for C <-> C++ bridging
	extern "C++" Ssr skillset_vector_to_ssr(std::vector<float> &skillsets) {
		//assert(skillsets.size() == NUM_Skillset);
		return Ssr {
			skillsets[Skill_Overall],
			skillsets[Skill_Stream],
			skillsets[Skill_Jumpstream],
			skillsets[Skill_Handstream],
			skillsets[Skill_Stamina],
			skillsets[Skill_JackSpeed],
			skillsets[Skill_Chordjack],
			skillsets[Skill_Technical],
		};
	}

	int calc_version() {
		return GetCalcVersion();
	}

	CalcHandle *create_calc() {
		return reinterpret_cast<CalcHandle*>(new Calc);
	}

	void destroy_calc(CalcHandle *calc) {
		delete reinterpret_cast<Calc*>(calc);
	}

	MsdForAllRates calc_msd(CalcHandle *calc, const NoteInfo *rows, size_t num_rows) {
		std::vector<NoteInfo> note_info(rows, rows + num_rows);

		auto msd_vectors = MinaSDCalc(
			note_info,
			reinterpret_cast<Calc*>(calc)
		);

		MsdForAllRates all_rates;
		for (int i = 0; i < 14; i++) {
			all_rates.msds[i] = skillset_vector_to_ssr(msd_vectors[i]);
		}

		return all_rates;
	}

	Ssr calc_ssr(CalcHandle *calc, NoteInfo *rows, size_t num_rows, float music_rate, float score_goal) {
		std::vector<NoteInfo> note_info(rows, rows + num_rows);

		auto skillsets = MinaSDCalc(
			note_info,
			music_rate,
			score_goal,
			reinterpret_cast<Calc*>(calc)
		);

		return skillset_vector_to_ssr(skillsets);
	}
}
