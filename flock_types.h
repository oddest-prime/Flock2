
#ifndef DEF_FLOCK_TYPES
	#define DEF_FLOCK_TYPES

	// Particle data
	#define FBIRD			0		
	#define FGCELL		1
	#define FGNDX			2	

	// Acceleration grid data
	#define AGRID			0	
	#define AGRIDCNT		1
	#define	AGRIDOFF		2
	#define AAUXARRAY1	3
	#define AAUXSCAN1		4
	#define AAUXARRAY2	5
	#define AAUXSCAN2		6

	#define GRID_UNDEF				2147483647			// max int
	#define SCAN_BLOCKSIZE		512		

	// GPU Kernels
	#define KERNEL_INSERT					0
	#define	KERNEL_COUNTING_SORT	1
	#define KERNEL_FIND_NBRS			2
	#define KERNEL_ADVANCE				3
	#define KERNEL_FPREFIXSUM			4
	#define KERNEL_FPREFIXFIXUP		5
	#define KERNEL_MAX						8

	#ifdef CUDA_KERNEL
		#include "quaternion.cuh"
		typedef float3			f3;
		typedef float4			f4;
		typedef int3				i3;	
		typedef quat4				q4;		
		#define ALIGN(n)		__align__(n)									// NVCC
	#else
		#include "quaternion.h"
		#include "vec.h"		
		typedef Vec4F			  f4;
		typedef Vec3F				f3;		
		typedef Vec3I				i3;
		typedef Quaternion	q4;
		#define ALIGN(n)		__declspec(align(n))					// MSVC
		//#define ALIGN(n)  __attribute__((aligned(n)))		// GCC
	#endif


	// *NOTE*
  // For GPU, a struct must follow memory alignment rules.
  // This includes each 4-component member var (float4, quat4) must have 128-bit alignment.
  // So we arrange those in the struct first, and ensure other align to 128-bits (16 bytes).
	//
	struct ALIGN(128) Bird {
		
		q4			orient;
		f4			clr;

		f3			pos, vel, accel, target;
		f3			ave_pos, ave_vel;
		
		float		speed, pitch_adv, power;	
		int			id, near_j, nbr_cnt;		
	};


	struct ALIGN(32) Accel {
		f3			bound_min, bound_max;
		float		psmoothradius, sim_scale;
		float		grid_size, grid_density;
		f3			gridSize, gridDelta, gridMin, gridMax;
		i3			gridRes, gridScanMax;
		int			gridSrch, gridTotal, gridAdjCnt, gridActive;
		int			gridAdj[64];	

		// gpu
		int			numThreads, numBlocks;
		int			gridThreads, gridBlocks;	
		int			szPnts;
	};

#endif
