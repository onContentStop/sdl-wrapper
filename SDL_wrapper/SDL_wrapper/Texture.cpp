#include "Texture.hpp"

#include "BlendMode.hpp"

sdl::Texture::Texture(std::unique_ptr<Texture> &&handle) : m_texture(std::move(handle))
{
}

Uint8 sdl::Texture::GetAlphaMod() const
{
    Uint8 alphaMod{};
    if (SDL_GetTextureAlphaMod(m_texture->Get(), &alphaMod) != 0)
    {
        throw std::runtime_error{
            Helpers::StringBuilder()
                .Add("Getting SDL texture alpha mod failed: ")
                .Add(SDL_GetError())
                .Build()};
    }
    return alphaMod;
}

sdl::BlendMode sdl::Texture::GetBlendMode() const
{
    SDL_BlendMode mode{};
    if (SDL_GetTextureBlendMode(m_texture->Get(), &mode) != 0)
    {
        throw std::runtime_error{
            Helpers::StringBuilder()
                .Add("Getting SDL texture blend mode failed: ")
                .Add(SDL_GetError())
                .Build()};
    }
    return BlendModeFromSdl(mode);
}

SDL_Color sdl::Texture::GetColorMod() const
{
    SDL_Color color{0, 0, 0, 0};
    if (SDL_GetTextureColorMod(m_texture->Get(), &color.r, &color.g, &color.b) !=
        0)
    {
        throw std::runtime_error{
            Helpers::StringBuilder()
                .Add("Getting SDL texture color mod failed: ")
                .Add(SDL_GetError())
                .Build()};
    }
    return color;
}

sdl::TextureAttributes sdl::Texture::Query() const
{
    TextureAttributes attributes{};
    if (SDL_QueryTexture(m_texture->Get(), &attributes.format, &attributes.access,
                         &attributes.w, &attributes.h) != 0)
    {
        throw std::runtime_error{
            Helpers::StringBuilder()
                .Add("Querying SDL texture attributes failed: ")
                .Add(SDL_GetError())
                .Build()};
    }

    return attributes;
}

// ReSharper disable once CppMemberFunctionMayBeConst
// not const because even though the handle is const-accessible, we shouldn't be
// able to set the alpha mod on a const Texture
//
// this logic also applies to the other setters
void sdl::Texture::SetAlphaMod(const Uint8 alpha)
{
    if (SDL_SetTextureAlphaMod(m_texture->Get(), alpha) != 0)
    {
        throw std::runtime_error{
            Helpers::StringBuilder()
                .Add("Setting SDL texture alpha mod failed: ")
                .Add(SDL_GetError())
                .Build()};
    }
}

SDL_Texture * sdl::Texture::Get() const noexcept
{
    return m_texture->Get();
}
