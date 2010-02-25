#ifndef __ObjReader_h__
#define __ObjReader_h__

#include "RE330_global.h"

namespace RE330 {

	class ObjReader
	{
	public:
		static void  readObj(char* fileName, int &nVertices, float **vertices, float **normals, 
							 float **texcoords, int &nIndices, int **indices);
        static void normalize(float *vertices, int nVertices);

	private:
		static void get_indices(char *word, int *vindex, int *tindex, int *nindex);
	};

}

#endif // CSCI330_OBJFILE_H_