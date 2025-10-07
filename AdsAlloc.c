#include <stdio.h>
#include <string.h>

struct Ad {
    char id[10];
    int duration;
    int deadline;
    int profit;           // Revenue in numbers
    char conflictGroup[10];
};

// Sort ads by profit/time ratio (Greedy)
void sortAds(struct Ad ads[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            double r1 = (double)ads[i].profit / ads[i].duration;
            double r2 = (double)ads[j].profit / ads[j].duration;
            if (r1 < r2) {
                struct Ad temp = ads[i];
                ads[i] = ads[j];
                ads[j] = temp;
            }
        }
    }
}

// Check for conflict group
int isConflictFree(struct Ad scheduled[], int count, struct Ad newAd) {
    int i;
    for (i = 0; i < count; i++) {
        if (strcmp(scheduled[i].conflictGroup, newAd.conflictGroup) == 0)
            return 0;
    }
    return 1;
}

int main() {
    int n, totalTime;
    printf("\n=== Smart Advertisement Slot Allocation System ===\n");

    printf("Enter total ad slots available (in minutes): ");
    scanf("%d", &totalTime);

    printf("Enter number of advertisements: ");
    scanf("%d", &n);

    struct Ad ads[100];
    int i;
    printf("\nEnter Ad details (ID Duration Deadline Profit ConflictGroup):\n");
    for (i = 0; i < n; i++) {
        scanf("%s %d %d %d %s",
              ads[i].id, &ads[i].duration, &ads[i].deadline,
              &ads[i].profit, ads[i].conflictGroup);
    }

    // Sort ads by profit/time ratio
    sortAds(ads, n);

    struct Ad scheduled[100];
    int count = 0, usedTime = 0, totalProfit = 0;

    printf("\nAllocating slots using Greedy Algorithm...\n\n");

    for (i = 0; i < n; i++) {
        if (usedTime + ads[i].duration <= totalTime && isConflictFree(scheduled, count, ads[i])) {
            scheduled[count++] = ads[i];
            usedTime += ads[i].duration;
            totalProfit += ads[i].profit;
        }
    }

    // Display final schedule
    printf("=== Final Advertisement Schedule ===\n");
    for (i = 0; i < count; i++) {
        printf("Ad %s | Duration: %d | Profit: %d | Group: %s\n",
               scheduled[i].id, scheduled[i].duration, scheduled[i].profit, scheduled[i].conflictGroup);
    }

    printf("\nTotal Broadcast Time Used: %d / %d minutes\n", usedTime, totalTime);
    printf("Total Revenue Generated: %d units\n", totalProfit);

    return 0;
}
