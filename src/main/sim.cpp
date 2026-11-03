#include <utility>

#include <glad/gl.h>

#include "main/sim.h"
#include "globals/globalStuff.h"
#include "gpu/shader.h"

void DrawFBO()
{
    glBindFramebuffer(GL_FRAMEBUFFER, ComputeFBOA);
    glViewport(0, 0, simWidth, simHeight);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void SimStep(double dt)
{
    computeShader.Use();
    computeShader.SetFloat("dt", (float)dt);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ComputeTexB);

    DrawFBO();

    // Ping pong
    std::swap(ComputeTexA, ComputeTexB);
    std::swap(ComputeFBOA, ComputeFBOB);
}