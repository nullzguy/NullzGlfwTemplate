#pragma once

void CreateTex1D(int width, unsigned int &texID);
void CreateTex2D(int width, int height, unsigned int &texID);
void CreateTex3D(int width, int height, int depth, unsigned int &texID);

void CreateTex1DUI(int width, unsigned int &texID);
void CreateTex2DUI(int width, int height, unsigned int &texID);
void CreateTex3DUI(int width, int height, int depth, unsigned int &texID);

void CreateFBO1D(unsigned int &FBOId, unsigned int &texID);
void CreateFBO2D(unsigned int &FBOId, unsigned int &texID);
void CreateFBO3D(unsigned int &FBOId, unsigned int &texID);

void CreateFBO1DUI(unsigned int &FBOId, unsigned int &texID);
void CreateFBO2DUI(unsigned int &FBOId, unsigned int &texID);
void CreateFBO3DUI(unsigned int &FBOId, unsigned int &texID);

void DestroyTex(unsigned int &texID);
void DestroyFBO(unsigned int &FBOId);
