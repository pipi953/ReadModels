// ReadModels.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <iostream>
#include <vector>

std::vector<float> ve;

void readModels(char const* path) {

	FILE* fp;
	fopen_s(&fp, "ModelData.h", "w");
	fprintf(fp, "float ModelVerts[] = {\n");

	Assimp::Importer importer;
	importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE, aiPrimitiveType_LINE | aiPrimitiveType_POINT);
	importer.SetPropertyInteger(AI_CONFIG_PP_PTV_NORMALIZE, true);

	unsigned flags = aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals;

	const aiScene* scene = importer.ReadFile(path, flags);

	if (!scene) {
		printf("model load error.\n");
		system("pause");
		return;
	}
	const aiMesh* mesh = scene->mMeshes[0];

	uint32_t numFaces = 0;
	std::unique_ptr<uint32_t[]> vertsIndex(new uint32_t[3 * mesh->mNumFaces]);

	numFaces = mesh->mNumFaces;
	for (unsigned i = 0; i < numFaces; i++) {
		vertsIndex[3 * i] = mesh->mFaces[i].mIndices[0];
		vertsIndex[3 * i + 1] = mesh->mFaces[i].mIndices[1];
		vertsIndex[3 * i + 2] = mesh->mFaces[i].mIndices[2];
	}

	std::cout << "~~~~~~~~~~" << mesh->mNumFaces << " " << std::endl;

	for (unsigned i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D tmp = mesh->mVertices[vertsIndex[i]];
		ve.push_back(tmp.x);
		ve.push_back(tmp.y);
		ve.push_back(tmp.z);

		ve.push_back(4.0f);
		ve.push_back(0.0f);
		ve.push_back(1.0f);
		ve.push_back(0.0f);

		fprintf(fp, "%ff, %ff, %ff, ", tmp.x, tmp.y, tmp.z);

		fprintf(fp, "%.0f.f, %ff, %ff, %ff,      ", 4.0, 0.0f, 1.0f, 0.0f);
		if ((i + 1) % 3 == 0)
			fprintf(fp, "\n");
	}

	fprintf(fp, "};\n\n");


}

int main()
{
	readModels("models/Stanford_Bunny/bunny.obj");

    std::cout << "Hello World!\n"; 
}




// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
