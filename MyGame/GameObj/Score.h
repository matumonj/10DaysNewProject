#pragma once

class Score final {
private:
	Score() = default;
	~Score() = default;
	Score(const Score& r) = default;
	Score& operator= (const Score& r) = default;
private:
	float score = 0;
public:
	static Score* GetIns() {
		static Score instans;
		return &instans;
	}		

	const float& GetScore() { return score; }

	void AddScore(const float& score) { this->score += score;}

	void ResetScore() { this->score = 0; }

};