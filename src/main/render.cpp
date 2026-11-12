#include "main/render.h"

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
