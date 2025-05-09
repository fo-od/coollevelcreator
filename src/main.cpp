#include "main.hpp"
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_sdlrenderer3.h>
#include <SDL3/SDL.h>
#include "globals.hpp"

bool running = false;

int main()
{
    if ( !init() ) {
        return 1;
    }
    running = true;
    while ( running ) {
        SDL_Event event;
        while ( SDL_PollEvent(&event) ) {
            handle_events(&event);
        }
        update();
        render();
    }
    cleanup();
    return 0;
}

bool init()
{
    if ( !SDL_SetAppMetadata("cool level creator", "1.0", "com.food.coollevelcreator") ) {
        SDL_Log("Couldn't set app metadata: %s", SDL_GetError());
        return false;
    }

    if ( !SDL_Init(SDL_INIT_VIDEO) ) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return false;
    }

    if ( !SDL_CreateWindowAndRenderer("cool level creator", 1024, 768, SDL_WINDOW_RESIZABLE, &window,
                                      &renderer) ) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return false;
    }

    // enable vsync
    if ( !SDL_SetRenderVSync(renderer, 1) ) {
        SDL_Log("Couldn't enable VSync: %s", SDL_GetError());
        return false;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Setup Platform/Renderer backends
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);

    return true;
}

void handle_events( const SDL_Event *event )
{
    if ( event->type == SDL_EVENT_QUIT ) {
        running = false;
    }
    if ( event->type == SDL_EVENT_WINDOW_RESIZED ) {
        SDL_GetWindowSizeInPixels(window, &windowWidth, &windowHeight);
    }
    ImGui_ImplSDL3_ProcessEvent(event);
}


void update()
{
    ImGui_ImplSDL3_NewFrame();
    ImGui_ImplSDLRenderer3_NewFrame();
    ImGui::NewFrame();
    ImGui::ShowDemoWindow();
}

void render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    ImGui::Render();
    ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

    SDL_RenderPresent(renderer);
}

void cleanup()
{
    // ImGui
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    // SDL
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
