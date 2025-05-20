//#include <iostream>
//#include <vector>
//#include <cstdint>
//#include <unordered_map>
//
//size_t dp(
//	int64_t positionMerchant, 
//	int64_t positionMe,
//	size_t C, 
//	size_t D,
//	std::unordered_map<std::pair<int64_t, int64_t>, 
//	size_t>& memo) {
//
//	// cost of this operation is 0
//	if (positionMerchant == positionMe) return 0;
//
//	auto it = memo.find(std::pair(positionMerchant, positionMe));
//
//	if (it != memo.end()) return it->second;
//	
//	if (positionMerchant > 0) {
//
//		if (positionMe > positionMerchant) {
//
//			size_t 
//				path1 = dp(positionMerchant - 1, positionMe, C, D, memo) + C,
//				path2 = dp(positionMerchant, positionMe - 1, C, D, memo) + D;
//
//			memo[std::pair(positionMerchant, positionMe)] = std::min(path1, path2);
//		}
//		else {
//
//			size_t
//				path1 = dp(positionMerchant - 1, positionMe, C, D, memo) + C,
//				path2 = dp(positionMerchant, positionMe + 1, C, D, memo) + D;
//
//			memo[std::pair(positionMerchant, positionMe)] = std::min(path1, path2);
//		}
//	}
//	else {
//
//		if (positionMe > positionMerchant) {
//
//			size_t
//				path1 = dp(positionMerchant + 1, positionMe, C, D, memo) + C,
//				path2 = dp(positionMerchant, positionMe + 1, C, D, memo) + D;
//
//			memo[std::pair(positionMerchant, positionMe)] = std::min(path1, path2);
//		}
//		else {
//
//			size_t
//				path1 = dp(positionMerchant + 1, positionMe, C, D, memo) + C,
//				path2 = dp(positionMerchant, positionMe - 1, C, D, memo) + D;
//
//			memo[std::pair(positionMerchant, positionMe)] = std::min(path1, path2);
//		}
//	}
//}
//
//int main() {
//
//	std::ios::sync_with_stdio(false);
//	std::cin.tie(nullptr);
//
//	size_t N = 0ULL, C = 0ULL, D = 0ULL;
//
//	std::cin >> N >> C >> D;
//
//	std::vector<int64_t> Merchants(N);
//
//	for (size_t i = 0; i < N; ++i) {
//
//		int64_t Merchanti = 0ULL;
//		std::cin >> Merchanti;
//
//		Merchants[i] = Merchanti;
//	}
//	
//	// solution
//
//	for (size_t i = 0; i < N; ++i) {
//
//
//
//	}
//
//	return 0;
//}

#include <iostream>
#include <vector>
#include <cmath>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t N, C, D;
    std::cin >> N >> C >> D;

    std::vector<int64_t> MerchantPositions(N);
    for (auto& MerchantPos : MerchantPositions) std::cin >> MerchantPos;

    int64_t CurrentPosition = 0;
    size_t TotalCost = 0;
    std::vector<int64_t> MeetPoints;

    for (size_t I = 0; I < N; ++I) {
        int64_t MerchantPosition = MerchantPositions[I];

        // Option 1: You move to the merchant
        size_t CostIfYouMove = std::abs(CurrentPosition - MerchantPosition) * C;

        // Option 2: Merchant moves to you
        size_t CostIfMerchantMoves = std::abs(CurrentPosition - MerchantPosition) * D;

        if (CostIfYouMove <= CostIfMerchantMoves) {
            TotalCost += CostIfYouMove;
            CurrentPosition = MerchantPosition;
        }
        else {
            TotalCost += CostIfMerchantMoves;
            // You stay, merchant comes to you
        }

        MeetPoints.push_back(CurrentPosition); // Record where item is collected
    }

    std::cout << TotalCost << "\n";
    for (auto Position : MeetPoints)
        std::cout << Position << " ";
    std::cout << "\n";

    return 0;
}
