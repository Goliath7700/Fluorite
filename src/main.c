#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_stdinc.h"
#include "SDL3/SDL_timer.h"
#include "SDL3/SDL_video.h"
#include "box2d/box2d.h"
#include "box2d/id.h"

bool initializeWindow();
b2WorldId initializeBox2D();
void renderMyStuff(SDL_Renderer *renderer);

SDL_Window *window;
SDL_Renderer *renderer;
SDL_WindowFlags windowFlags =
    SDL_WINDOW_RESIZABLE;
static int windowWidth = 640;
static int windowHeight = 480;

int main(void) {
    if (!initializeWindow()) {return SDL_APP_FAILURE;}
    b2WorldId worldId = initializeBox2D();

    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    groundBodyDef.position = (b2Pos){0.0f, -10.0f};
    b2BodyId groundId = b2CreateBody(worldId, &groundBodyDef);
    b2Polygon groundBox = b2MakeBox(50.0f, 10.0f);
    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = (b2Pos){0.0f, 4.0f};
    b2BodyId bodyId = b2CreateBody(worldId, &bodyDef);
    b2Polygon dynamicBox = b2MakeBox(1.0f, 1.0f);
    b2ShapeDef shapeDef = b2DefaultShapeDef();
    shapeDef.density = 1.0f;
    shapeDef.material.friction = 0.3f;
    b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);

    float timeStep = 1.0f / 60.0f;
    int subStepCount = 4;

    SDL_Event event;
    bool running = true;

    while (running) {
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);

        b2World_Step(worldId, timeStep, subStepCount);
        b2Pos position = b2Body_GetPosition(bodyId);
        SDL_Log("%4.2f %4.2f", position.x, position.y);
        renderMyStuff(renderer);

        // QUIT
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                SDL_Quit();
                SDL_Log("quitting!");
                running = false;
                return 0;
            }
        }
    }

    return 0;
}

bool initializeWindow() {
    SDL_SetAppMetadata("Fluorite", "1.0", "io.github.goliath7700.fluorite");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return false;
    }

    if (!SDL_CreateWindowAndRenderer("Fluorite", windowWidth, windowHeight, windowFlags, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return false;
    }
    SDL_SetRenderLogicalPresentation(renderer, 640, 480, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    return true;
}

b2WorldId initializeBox2D() {
    b2WorldDef worldDef = b2DefaultWorldDef();
    worldDef.gravity = (b2Vec2){0.0f, -10.0f};

    b2WorldId worldId = b2CreateWorld(&worldDef);

    return worldId;
}

void renderMyStuff(SDL_Renderer *renderer) {
    const double now = ((double)SDL_GetTicks()) / 1000.0;  /* convert from milliseconds to seconds. */

    /* choose the color for the frame we will draw. The sine wave trick makes it fade between colors smoothly. */
    const float red = (float) (0.5 + 0.5 * SDL_sin(now));
    const float green = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 2 / 3));
    const float blue = (float) (0.5 + 0.5 * SDL_sin(now + SDL_PI_D * 4 / 3));
    SDL_SetRenderDrawColorFloat(renderer, red, green, blue, SDL_ALPHA_OPAQUE_FLOAT);  /* new color, full alpha. */

    /* clear the window to the draw color. */
    SDL_RenderClear(renderer);

    SDL_SetRenderScale(renderer, 2, 2);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderDebugText(renderer, 0, 0, "Installing Free RAM!!!!!!");
    /* put the newly-cleared rendering on the screen. */
    SDL_RenderPresent(renderer);
}
