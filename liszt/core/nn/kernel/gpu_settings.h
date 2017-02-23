#ifndef GPUSETTINGS_H
#define GPUSETTINGS_H

#define THREADS_PER_BLOCK 512
#define N_BLOCKS(M) (M + THREADS_PER_BLOCK - 1) / THREADS_PER_BLOCK

#endif
