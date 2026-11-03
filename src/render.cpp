#include <glad/gl.h>
#include <glm/glm.hpp>

#include "render.h"
#include "globalStuff.h"
#include "shader.h"

void BindFBO(int FrameFBO)
{
    glBindFramebuffer(GL_FRAMEBUFFER, FrameFBO);
    glViewport(0, 0, renderWidth, renderHeight);
}

void Render()
{
    BindFBO(FrameFBO);

    fragmentShader.Use();
    fragmentShader.SetVec2("res", glm::vec2((float)renderWidth, (float)renderHeight));
    fragmentShader.SetInt("computeTex", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ComputeTexB);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // Blit
    glBindFramebuffer(GL_READ_FRAMEBUFFER, FrameFBO);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, renderWidth, renderHeight,
                      0, 0, screenWidth, screenHeight,
                      GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, screenWidth, screenHeight);
}
