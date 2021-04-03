#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename tA, typename tB=null_type> using ord_set = tree<tA, tB, std::less<tA>, rb_tree_tag, tree_order_statistics_node_update>;
/** Instructions:
 * If you want to use it like a set: ord_set<int> st;
 * If you want to use it like a map: ord_set<int, int> mp;
 * ====== Functions ======
 * insert, erase, lower_bound, upper_bound, find, just like normal set
 * s.order_of_key(k); -----> qtt of strictly smaller than k, O(logN)
 * s.find_by_order(k); ----> iterator to k-th element counting from 0, in O(logN)
*/