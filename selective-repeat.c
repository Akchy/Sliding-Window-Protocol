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
    int sent_frames[TOTAL_FRAMES] = {0};  // Keeps track of which frames are sent
    int ack_frames[TOTAL_FRAMES] = {0};  // Keeps track of which frames are acknowledged
    int base = 0;  // Base of the sliding window
    int next_frame = 0;  // Next frame to send
    int i;

    srand(time(0));  // Seed for random number generation

    printf("Simulating Selective Repeat Sliding Window Protocol...\n\n");

    while (base < TOTAL_FRAMES) {
        // Send all frames in the window
        for (i = 0; i < WINDOW_SIZE && (base + i) < TOTAL_FRAMES; i++) {
            int frame_to_send = base + i;
            if (!sent_frames[frame_to_send]) {  // If frame is not sent yet
                printf("Sending frame %d\n", frame_to_send);
                sent_frames[frame_to_send] = 1;
            }
        }

        // Simulate acknowledgment for each frame in the window
        for (i = 0; i < WINDOW_SIZE && (base + i) < TOTAL_FRAMES; i++) {
            int frame_to_check = base + i;
            if (!ack_frames[frame_to_check]) {  // If frame is not acknowledged yet
                if (is_frame_lost()) {
                    printf("Frame %d lost! Retransmitting later...\n", frame_to_check);
                } else {
                    printf("Frame %d acknowledged.\n", frame_to_check);
                    ack_frames[frame_to_check] = 1;
                }
            }
        }

        // Move the sliding window
        while (base < TOTAL_FRAMES && ack_frames[base]) {
            printf("Sliding window: Base moved from %d to %d\n", base, base + 1);
            base++;
        }
    }

    printf("\nAll frames sent and acknowledged successfully!\n");

    return 0;
}
