#include "FrameBufferEmulator.h"
#include <iostream> 

static int b[1000];
static int N = 0;
static bool isTriangle = false;
static bool isInitialized = false;

void FrameBufferEmulator::initUser()
{
    //入力
    N = 6;
    b[0] = 1; b[1] = 4; b[2] = 1; b[3] = 3; b[4] = 2; b[5] = 4;
    isTriangle = false;
    isInitialized = true;
}

// 描画処理
void FrameBufferEmulator::drawUser(unsigned char* buff, int mode, int keyLevel, int keyTrigger)
{
    if (isInitialized) initUser();

    if (keyTrigger == SDLK_RIGHT && !isTriangle) {

        // 三角形判定
        isTriangle = true;

        if (b[0] != 1) isTriangle = false;
        else {
            for (int i = 1; i < N; i++) {
                if (b[i] != b[i - 1] + 1) { isTriangle = false; break; }
            }
        }

        // 三角形でなければ、次の状態
        if (!isTriangle) {

            int tmp[1000];
            int m = 0;

            for (int i = 0; i < N; i++) {
                if (b[i] > 1) tmp[m++] = b[i] - 1;
            }

            for (int i = 0; i < m; i++) b[i] = tmp[i];
            b[m] = N;
            N = m + 1;
        }
    }

   
    for (int i = 0; i < width * height * 3; i++) {
        buff[i] = 0;
    }

    
    int blockSize = 20; 
    for (int i = 0; i < N; i++) {
        for (int h = 0; h < b[i]; h++) {
    
            int startX = 30 + i * (blockSize + 2);
            int startY = (height - 30) - h * (blockSize + 2);

            for (int dy = 0; dy < blockSize; dy++) {
               
                for (int dx = 0; dx < blockSize; dx++) {
                    
                    int px = startX + dx;
                    int py = startY - dy;
                    
                    if (px >= 0 && px < width && py >= 0 && py < height) {
                        int pos = (py * width + px) * 3;
                        buff[pos + 0] = 100; // B
                        buff[pos + 1] = 0; // G
                        buff[pos + 2] = 0; // R
                    }
                }
            }
        }
    }
}
