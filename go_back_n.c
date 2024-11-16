#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define WINDOW_SIZE 4  // Size of the sliding window
#define TOTAL_FRAMES 10  // Total number of frames to send

// Function to simulate whether a frame is successfully transmitted or lost
bool is_frame_lost() {
    return rand() % 5 == 0;  // Simulate a 20% chance of frame loss
}

int main() {
    int base = 0;          // Base of the sliding window
    int next_frame = 0;    // Next frame to send
    int ack[TOTAL_FRAMES] = {0};  // Array to track acknowledgments
    int i;

    srand(time(0));  // Seed for random number generation

    printf("Simulating Go-Back-N Sliding Window Protocol...\n\n");

    while (base < TOTAL_FRAMES) {
        // Send frames within the window
        for (i = 0; i < WINDOW_SIZE && (base + i) < TOTAL_FRAMES; i++) {
            int frame_to_send = base + i;
            if (frame_to_send >= next_frame) {
                printf("Sending frame %d\n", frame_to_send);
            }
        }

        // Simulate acknowledgment for each frame
        for (i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            if (!ack[i]) {  // If frame is not acknowledged
                if (is_frame_lost()) {
                    printf("Frame %d lost! Retransmitting all frames from %d onwards...\n", i, base);
                    break;  // Stop and retransmit from the base frame
                } else {
                    printf("Frame %d acknowledged.\n", i);
                    ack[i] = 1;  // Mark frame as acknowledged
                }
            }
        }

        // Move the base if frames are acknowledged sequentially
        while (base < TOTAL_FRAMES && ack[base]) {
            printf("Sliding window: Base moved from %d to %d\n", base, base + 1);
            base++;
        }

        // Update the next frame to send
        next_frame = base;
    }

    printf("\nAll frames sent and acknowledged successfully!\n");

    return 0;
}
