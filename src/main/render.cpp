#include "main/render.h"

void InitShaders() {
    computeShader = shader(SHADER_DIR "/vertex.glsl", SHADER_DIR "/compute.glsl");
    fragmentShader = shader(SHADER_DIR "/vertex.glsl", SHADER_DIR "/fragment.glsl");
}

void InitRenderTargets(int width, int height, int compWidth, int compHeight) {
    renderWidth = width;
    renderHeight = height;
    screenWidth = width;
    screenHeight = height;
    simWidth = compWidth;
    simHeight = compHeight;

    // Compute A/B tex&FBO creation
    CreateTex2DUI(compWidth, compHeight, ComputeTexA);
    CreateTex2DUI(compWidth, compHeight, ComputeTexB);
    CreateFBO2DUI(ComputeFBOA, ComputeTexA);
    CreateFBO2DUI(ComputeFBOB, ComputeTexB);

    // And for frame
    CreateTex2D(width, height, FrameTex);
    CreateFBO2D(FrameFBO0, FrameTex);

    // Texture bindings
    computeShader.Use();
    computeShader.SetInt("simTexA", 0);
    fragmentShader.Use();
    fragmentShader.SetInt("computeTex", 0);

    // Make the compute textures empty
    glBindFramebuffer(GL_FRAMEBUFFER, ComputeFBOA);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindFramebuffer(GL_FRAMEBUFFER, ComputeFBOB);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void BlitFBO(int FBO) {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, FrameFBO0);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, renderWidth, renderHeight,
                      0, 0, screenWidth, screenHeight,
                      GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, screenWidth, screenHeight);
}

void Render() {
    BlitFBO(FrameFBO0);

    glBindFramebuffer(GL_FRAMEBUFFER, FrameFBO0);
    glViewport(0, 0, renderWidth, renderHeight);

    fragmentShader.Use();
    fragmentShader.SetVec2("res", glm::vec2((float)renderWidth, (float)renderHeight));
    fragmentShader.SetInt("computeTex", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ComputeTexB);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    BlitFBO(FrameFBO0);
}
