#include "lcs.h"

using namespace std;

int** fill_LCS(const string& first, const string& second) {
	// Return LCS matrix

	int** LCS = new int* [first.size() + 1];
	for (int i = 0; i < first.size() + 1; i++)
		LCS[i] = new int[second.size() + 1] {};

	for (size_t i = 1; i <= first.size(); i++)
		for (size_t j = 1; j <= second.size(); j++) {
			if (first[i - 1] == second[j - 1])
				LCS[i][j] = LCS[i - 1][j - 1] + 1;
			else
				LCS[i][j] = max(LCS[i - 1][j], LCS[i][j - 1]);
		}

	return LCS;
}

string lcs(const string& first, const string& second) {
	// Return the longest common subsequence (LCS) of the two given strings.

	int** LCS = fill_LCS(first, second);

	string my_lsc = "";

	for (size_t i = first.size(), j = second.size(); i > 0 && j > 0;) {
		if (first[i - 1] == second[j - 1]) {
			my_lsc.insert(0, 1, first[i - 1]);
			i--; j--;
		}
		else {
			if (LCS[i - 1][j] > LCS[i][j - 1])
				i--;
			else
				j--;
		}
	}

	return my_lsc;
}

//string lcs(const string& first, const string& second) {
//	// Return the longest common subsequence (LCS) of the two given strings.
//
//	size_t i = first.size(), j = second.size();
//
//	if (i == 0 || j == 0)
//		return "";
//	else {
//		if (first[i - 1] == second[j - 1]) {
//			string str = lcs(first.substr(0, i - 1), second.substr(0, j - 1));
//			str.insert(str.size(), 1, first[i - 1]);
//			return str;
//		}
//		else {
//			string str1 = lcs(first.substr(0, i - 1), second.substr(0, j));
//			string str2 = lcs(first.substr(0, i), second.substr(0, j - 1));
//			return str1.size() > str2.size() ? str1 : str2;
//		}
//	}
//}