#include "MinaCalc.h"

extern "C" {
	struct CalcHandle;

	struct Ssr {
		float overall;
		float stream;
		float jumpstream;
		float handstream;
		float stamina;
		float jackspeed;
		float chordjack;
		float technical;
	};

	struct MsdForAllRates {
		// one for each full-rate from 0.7 to 2.0 inclusive
		Ssr msds[14];
	};

	// internal utility function
	extern "C++" Ssr skillset_vector_to_ssr(std::vector<float> &skillsets) {
		//assert(skillsets.size() == NUM_Skillset);
		return Ssr {
			.overall = skillsets[Skill_Overall],
			.stream = skillsets[Skill_Stream],
			.jumpstream = skillsets[Skill_Jumpstream],
			.handstream = skillsets[Skill_Handstream],
			.stamina = skillsets[Skill_Stamina],
			.jackspeed = skillsets[Skill_JackSpeed],
			.chordjack = skillsets[Skill_Chordjack],
			.technical = skillsets[Skill_Technical],
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