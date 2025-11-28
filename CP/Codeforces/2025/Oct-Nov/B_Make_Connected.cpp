#include <iostream>
#include <string>
#include <vector>

using namespace std;

int n;
vector<string> grid;
vector<vector<bool>> visited;
vector<vector<bool>> is_usable;

// Standard 4-directional moves for DFS
int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};

// Check if a cell is within the grid boundaries
bool isValid(int r, int c) { return r >= 0 && r < n && c >= 0 && c < n; }

// --- MODIFIED DFS ---
// Added parent (pr, pc) to track the path
int dfs(int r, int c, int pr, int pc) {
    if (visited[r][c]) {
        return 0;
    }
    visited[r][c] = true;

    // Count this cell only if it was an *initial* black cell
    int count = (grid[r][c] == '#');

    for (int i = 0; i < 4; ++i) {
        int nr = r + dr[i];
        int nc = c + dc[i];

        // Don't go back to the parent
        if (nr == pr && nc == pc) continue;

        // Check bounds, visited, and "usable" status
        if (isValid(nr, nc) && !visited[nr][nc] && is_usable[nr][nc]) {
            // --- NEW 3-IN-A-ROW CHECK ---
            // This checks if the path itself is creating a 3-in-a-row
            // (e.g., from (pr,pc) -> (r,c) -> (nr,nc))
            bool forbidden_move = false;
            // Check if current, next, AND parent are all white cells
            if (grid[r][c] == '.' && grid[nr][nc] == '.') {
                if (pr != -1 && grid[pr][pc] == '.') {
                    // Check if parent, current, and next form a straight line
                    if (pr == r && r == nr) {  // Horizontal line
                        forbidden_move = true;
                    }
                    if (pc == c && c == nc) {  // Vertical line
                        forbidden_move = true;
                    }
                }
            }

            if (forbidden_move) {
                continue;  // This move is forbidden, skip it
            }
            // --- END OF NEW CHECK ---

            count += dfs(nr, nc, r, c);  // Pass current (r,c) as new parent
        }
    }
    return count;
}

bool solve() {
    cin >> n;
    grid.assign(n, "");
    visited.assign(n, vector<bool>(n, false));
    is_usable.assign(n, vector<bool>(n, false));

    int initial_black_count = 0;
    int start_r = -1, start_c = -1;

    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    // --- Step 1: Initial 3-in-a-row Check ---
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            // Find first black cell for DFS start
            if (grid[i][j] == '#') {
                initial_black_count++;
                if (start_r == -1) {
                    start_r = i;
                    start_c = j;
                }
            }

            // Check horizontal 3-in-a-row
            if (j + 2 < n && grid[i][j] == '#' && grid[i][j + 1] == '#' &&
                grid[i][j + 2] == '#') {
                return false;
            }
            // Check vertical 3-in-a-row
            if (i + 2 < n && grid[i][j] == '#' && grid[i + 1][j] == '#' &&
                grid[i + 2][j] == '#') {
                return false;
            }
        }
    }

    // --- Step 2: All-White Grid ---
    if (initial_black_count == 0) {
        return true;
    }

    // --- Step 3: Build the "Usable" Graph (CORRECTED) ---
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == '#') {
                is_usable[i][j] = true;
                continue;  // Go to the next cell
            }

            // This is a WHITE cell ('.')
            // Check if painting it is forbidden because it would
            // create a 3-in-a-row with *initial* black cells.

            bool forbidden = false;

            // 1. Check # . # (horizontal)
            if (isValid(i, j - 1) && grid[i][j - 1] == '#' &&
                isValid(i, j + 1) && grid[i][j + 1] == '#') {
                forbidden = true;
            }

            // 2. Check # . # (vertical)
            if (isValid(i - 1, j) && grid[i - 1][j] == '#' &&
                isValid(i + 1, j) && grid[i + 1][j] == '#') {
                forbidden = true;
            }

            // 3. Check ##. (horizontal, we are the '.')
            if (isValid(i, j - 1) && grid[i][j - 1] == '#' &&
                isValid(i, j - 2) && grid[i][j - 2] == '#') {
                forbidden = true;
            }

            // 4. Check .## (horizontal, we are the '.')
            if (isValid(i, j + 1) && grid[i][j + 1] == '#' &&
                isValid(i, j + 2) && grid[i][j + 2] == '#') {
                forbidden = true;
            }

            // 5. Check ##. (vertical, we are the '.')
            if (isValid(i - 1, j) && grid[i - 1][j] == '#' &&
                isValid(i - 2, j) && grid[i - 2][j] == '#') {
                forbidden = true;
            }

            // 6. Check .## (vertical, we are the '.')
            if (isValid(i + 1, j) && grid[i + 1][j] == '#' &&
                isValid(i + 2, j) && grid[i + 2][j] == '#') {
                forbidden = true;
            }

            // Only usable if not forbidden by any pattern
            if (!forbidden) {
                is_usable[i][j] = true;
            }
        }
    }

    // --- Step 4: Final DFS (MODIFIED) ---
    // Start the DFS with no parent (-1, -1)
    int visited_black_count = dfs(start_r, start_c, -1, -1);

    // Check if all initial black cells were reachable
    return visited_black_count == initial_black_count;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        if (solve()) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}