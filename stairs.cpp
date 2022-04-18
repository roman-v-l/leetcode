#include <iostream>
#include <vector>

        struct last_step_count {
            int ones;
            int twos;
        };

    int climbStairs(int n) {
    
        std::vector<last_step_count> counts(n);
            
        counts[1].ones = 1;
        counts[1].twos = 0;
        
        counts[2].ones = 1;
        counts[2].twos = 1;

        for (int i = 3; i <= n; ++i)
        {
            counts[i].ones = counts[i-1].ones + counts[i-1].twos;
            counts[i].twos = counts[i-1].ones;
        }
        
        return counts[n].ones + counts[n].twos;
    };

int main()
{
    std::cout << "Test for n=3: " << climbStairs(3) << std::endl;
    std::cout << "Test for n=4: " << climbStairs(4) << std::endl;
    std::cout << "Test for n=5: " << climbStairs(5) << std::endl;
    std::cout << "Test for n=6: " << climbStairs(6) << std::endl;

    return 0;
}
