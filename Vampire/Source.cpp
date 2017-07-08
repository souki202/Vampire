#include <iostream>
#include <iomanip>
#include <vector>
#include <cstring>
#include <cmath>
#include <algorithm>
#undef max
#undef min

bool field[41][22] = {false};
bool field2[20][22] = { false };
constexpr int SUN_OFFSET_X = 20;
int main() {
	int r, n;
	while (std::cin >> r >> n && (r || n)) {
		std::memset(field, false, sizeof(bool) * 41 * 22);
		std::memset(field2, false, sizeof(bool) * 20 * 22);
		for (int i = 0; i < n; i++) {
			int x[2], h;
			std::cin >> x[0] >> x[1] >> h;
			x[0] += SUN_OFFSET_X; x[1] += SUN_OFFSET_X;
			//黒で塗りつぶす
			for (int j = 0; j < h; j++) {
				for (int k = x[0]; k < x[1]; k++) {
					field[k][j] = true;
				}
			}
		}
		
		std::vector<double> circleHeights;
		for (int i = 0; i < 20; i++) {
			//簡単にするため、xが負の方を正の方にコピーし、重複部分だけを残す
			for (int j = 0; j < 21; j++) {
				field2[19 - i][j] = field[i][j] && field[39 - i][j];
			}
		}

		for (int i = 0; i < r; i++) {
			//円のそれぞれのxでのy=0に対する増分
			//h^2 + i^2 = r^2 
			//h^2 = r^2 - i^2
			circleHeights.push_back(-r + std::sqrt(r  * r - i * i));
		}

		std::vector<double> heights;
		for (int i = 0; i < r; i++) {
			int h = 0;
			for (h = 0; h < 21; h++) {
				if (!field2[i][h]) break;
			}
			heights.push_back(h);
		}

		//高さ補正
		for (int i = 0; i < heights.size(); i++) {
			heights[i] -= circleHeights[i];
		}

		//最小を探す
		double min = 9999;
		for (int i = 0; i < heights.size(); i++) {
			min = std::min(min, heights[i]);
		}
		std::cout << std::fixed << std::setprecision(4) << min << std::endl;
	}
	return 0;
}