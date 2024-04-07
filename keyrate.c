#include <windows.h>
#include <stdlib.h>
#include <stdio.h>

const int MIN_DELAY_MS = 150;
const int MIN_REPEAT_MS = 1;

int trySetKeyRate(FILTERKEYS* keys) {
    if (!SystemParametersInfo(SPI_SETFILTERKEYS, 0, (LPVOID) keys, 0)) {
        fprintf(stderr, "System call failed - Unable to set keyrate.");
        return 1;
    }

    return 0;
}

int main(int argc, char* argv[]) {
    FILTERKEYS keys = { sizeof(FILTERKEYS) };

    long argDelayMs;
    long argRepeatMs;

    if (argc == 3) {
        char* end1;
        char* end2;

        argDelayMs = strtol(argv[1], &end1, 10);
        argRepeatMs = strtol(argv[2], &end2, 10);
    }
    else if (argc == 1) {
        puts("Disabled keyrate");
        return trySetKeyRate(&keys);
    }
    else {
        puts("Usage: keyrate.exe [delay] [repeat]\n");
        puts("Arguments:");
        printf(
            "  [delay]   the delay (ms) before the held key starts repeating (min. %d)\n",
            MIN_DELAY_MS
        );
        printf(
            "  [repeat]  the pause (ms) between each repeated key input (min. %d)\n\n",
            MIN_REPEAT_MS
        );
        return 0;
    }

    if (argDelayMs < MIN_DELAY_MS || argRepeatMs < MIN_REPEAT_MS) {
        puts("Invalid input - Minimum values are:");
        printf(
            "Delay: %dms | Rate: %dms\n",
            MIN_DELAY_MS,
            MIN_REPEAT_MS
        );
        return 0;
    }

    keys.iDelayMSec = argDelayMs;
    keys.iRepeatMSec = argRepeatMs;

    keys.dwFlags = FKF_FILTERKEYSON|FKF_AVAILABLE;

    if (trySetKeyRate(&keys) == 1) {
        return 1;
    }

    printf(
        "Set keyrate - Delay: %dms | Rate: %dms\n",
        keys.iDelayMSec,
        keys.iRepeatMSec
    );

    return 0;
}
