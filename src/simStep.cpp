#include <utility>

#include <glad/gl.h>

#include "simStep.h"
#include "globalStuff.h"
#include "shader.h"

void SimStep(double dt)
{
    shader& compute = computeShader();
    compute.Use();
    compute.SetFloat("dt", (float)dt);

    // Read ComputeTexB, write the result into ComputeTexA
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, ComputeTexB);

    glBindFramebuffer(GL_FRAMEBUFFER, ComputeFBOA);
    glViewport(0, 0, renderWidth, renderHeight);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Ping-pong
    std::swap(ComputeTexA, ComputeTexB);
    std::swap(ComputeFBOA, ComputeFBOB);
}