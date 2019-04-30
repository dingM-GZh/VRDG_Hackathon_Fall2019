#include <fstream>
#include <time.h>
#include <pthread.h>

using namespace std;
int len;
int radius;
int angle;
int color;
int treeCount = 0;

pthread_cond_t lenCon = PTHREAD_COND_INITIALIZER;
pthread_cond_t radCon = PTHREAD_COND_INITIALIZER;
pthread_cond_t angleCon = PTHREAD_COND_INITIALIZER;
pthread_cond_t colorCon = PTHREAD_COND_INITIALIZER;
pthread_cond_t treeCountCon = PTHREAD_COND_INITIALIZER;

pthread_mutex_t lenMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t radMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t angleMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t colorMutex = PTHREAD_MUTEX_INITIALIZER;

void *initLen(void *) {
    pthread_mutex_lock(&lenMutex);
    int temp = rand() + 2999;
    if (rand() % 2) {
        len = 40 + (temp % 20);
    } else {
        len = 40 - (temp % 20);
    }
    pthread_mutex_unlock(&lenMutex);
    return NULL;
}
void *initRadius(void *)
{
    pthread_mutex_lock(&radMutex);
    int temp = rand() + 4001;
    if (rand() % 2) {
        radius = 6 + (rand() % 4);
    } else {
        radius = 6 - (rand() % 4);
    }
    pthread_mutex_unlock(&radMutex);
    return NULL;
}
void *initAngle(void *)
{
    pthread_mutex_lock(&radMutex);
    int temp = rand() + 4993;
    angle = temp % 3601;
    pthread_cond_signal(&treeCountCon);
    pthread_mutex_unlock(&radMutex);
    return NULL;
}
void *initColor(void *)
{
    pthread_mutex_lock(&radMutex);
    int temp = rand() + 5879;
    color = temp % 1001;
    pthread_mutex_unlock(&radMutex);
    return NULL;
}
void *initTreeCount(void *)
{
    pthread_mutex_lock(&angleMutex);
    pthread_cond_wait(&treeCountCon, &angleMutex);
    int temp = angle;
    while (temp >= 0) {
        temp -= 360;
        treeCount++;
    }
    pthread_mutex_unlock(&angleMutex);
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t lenThread;
    pthread_t radThread;
    pthread_t angleThread;
    pthread_t colorThread;
    pthread_t treeCountThread;
    pthread_create(&lenThread, NULL, initLen, NULL);
    pthread_create(&radThread, NULL, initRadius, NULL);
    pthread_create(&treeCountThread, NULL, initTreeCount, NULL);
    pthread_create(&angleThread, NULL, initAngle, NULL);
    pthread_create(&colorThread, NULL, initColor, NULL);
    pthread_join(lenThread, NULL);
    pthread_join(radThread, NULL);
    pthread_join(angleThread, NULL);
    pthread_join(colorThread, NULL);
    pthread_join(treeCountThread, NULL);
    ofstream fout;
    fout.open("data.txt");
    fout << radius << ",";
    fout << len << ",";
    fout << angle << ",";
    fout << color << ",";
    fout << treeCount;
    fout.close();

    pthread_mutex_destroy(&lenMutex);
    pthread_mutex_destroy(&radMutex);
    pthread_mutex_destroy(&angleMutex);
    pthread_mutex_destroy(&colorMutex);

    pthread_cond_destroy(&lenCon);
    pthread_cond_destroy(&radCon);
    pthread_cond_destroy(&angleCon);
    pthread_cond_destroy(&colorCon);
    pthread_cond_destroy(&treeCountCon);

    pthread_exit(NULL);

    return 0;
}