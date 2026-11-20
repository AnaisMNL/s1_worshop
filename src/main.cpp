#include <sil/sil.hpp>
#include "random.hpp"
#include <cmath>
#include <string>
#include <algorithm>

// exo1
void exo1(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        color.r = 0.f;
        color.b = 0.f;
    }
}

// exo2
void exo2(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
    std::swap(color.r, color.b);
    }
}

// exo3
void exo3(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        float gris = (color.r + color.g + color.b) / 3.f;
        color = glm::vec3{gris};
    }
}

// exo4
void exo4(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        color = 1.f - color;
    }
}

// exo5
void exo5(sil::Image& image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            float ratio = static_cast<float>(x) / (image.width() - 1);
            image.pixel(x, y) = glm::vec3{ratio};
        }
    }
}

// exo6
void exo6(sil::Image& image)
{
    for (int x{0}; x < image.width() / 2; x++)
    {
        for (int y{0}; y < image.height () ; y++)
        {
            std::swap(image.pixel(x,y), image.pixel(image.width() - 1 - x,y));
        }
    }
}

// exo7
void exo7(sil::Image& image)
{
    for (glm::vec3& color : image.pixels())
    {
        if (true_with_probability(0.3f))
        {
            color.r = random_float(0.f, 1.f);
            color.g = random_float(0.f, 1.f);
            color.b = random_float(0.f, 1.f);
        }
    }
}

// exo8
void exo8(sil::Image& image)
{
    sil::Image result{image.height(), image.width()};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            result.pixel(image.height() - 1 - y, x) = image.pixel(x, y);
        }
    }

    image = result;
}

// exo9
void exo9(sil::Image& image)
{
    sil::Image copy = image;
    int offset = 30;

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = 0.f;
            image.pixel(x, y).b = 0.f;

            if (x + offset < image.width())
            {
                image.pixel(x, y).r = copy.pixel(x + offset, y).r;
            }

            if (x - offset >= 0)
            {
                image.pixel(x, y).b = copy.pixel(x - offset, y).b;
            }
        }
    }
}

// exo10
void exo10(sil::Image& image, float factor)
{
    for (glm::vec3& color : image.pixels())
    {
        color.r = std::pow(color.r, factor);
        color.g = std::pow(color.g, factor);
        color.b = std::pow(color.b, factor);
    }
}

// exo11
void exo11(sil::Image& image, int center_x, int center_y, int radius)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            int dx = x - center_x;
            int dy = y - center_y;

            if (dx * dx + dy * dy <= radius * radius)
            {
                image.pixel(x, y) = glm::vec3{1.f};
            }
        }
    }
}

// exo12
void exo12(sil::Image& image, int center_x, int center_y, int radius, int thickness)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            int dx = x - center_x;
            int dy = y - center_y;
            int dist_sq = dx * dx + dy * dy; 
            
            if (dist_sq <= radius * radius && dist_sq >= (radius - thickness) * (radius - thickness))
            {
                image.pixel(x, y) = glm::vec3{1.f}; 
            }
        }
    }
}

// exo13
// -> main

// exo14
void exo14(sil::Image& image, int center_x, int center_y, int radius, int thickness)
{
    exo12(image, center_x, center_y, radius, thickness);

    int nb_circles = 6;
    float pi = 3.14159265f;

    for (int i{0}; i < nb_circles; i++)
    {
        float angle = i * (2.f * pi / nb_circles);

        int x = center_x + static_cast<int>(radius * std::cos(angle));
        int y = center_y + static_cast<int>(radius * std::sin(angle));

        exo12(image, x, y, radius, thickness);
    }
}

// exo15
void exo15(sil::Image& image, int repeat_x, int repeat_y)
{
    sil::Image result{image.width() * repeat_x, image.height() * repeat_y};

    for (int x{0}; x < result.width(); x++)
    {
        for (int y{0}; y < result.height(); y++)
        {
            int orig_x = x % image.width();
            int orig_y = y % image.height();

            result.pixel(x, y) = image.pixel(orig_x, orig_y);
        }
    }

    image = result;
}

// exo17
void exo17(sil::Image& image)
{
    int nb_glitches = 40;

    for (int i{0}; i < nb_glitches; i++)
    {
        int rect_width  = random_int(10, 60);
        int rect_height = random_int(2, 12);

        int x1 = random_int(0, image.width() - rect_width);
        int y1 = random_int(0, image.height() - rect_height);

        int x2 = random_int(0, image.width() - rect_width);
        int y2 = random_int(0, image.height() - rect_height);

        for (int dx{0}; dx < rect_width; dx++)
        {
            for (int dy{0}; dy < rect_height; dy++)
            {
                std::swap(image.pixel(x1 + dx, y1 + dy), image.pixel(x2 + dx, y2 + dy));
            }
        }
    }
}

// exo18




int main()
{
    {
        sil::Image image{"images/logo.png"};
        exo1(image);
        image.save("output/exo1.png");
    } 

    {
        sil::Image image{"images/logo.png"}; 
        exo2(image);
        image.save("output/exo2.png");
    }

    {
        sil::Image image{"images/logo.png"}; 
        exo3(image);
        image.save("output/exo3.png");
    }

    {
        sil::Image image{"images/logo.png"}; 
        exo4(image);
        image.save("output/exo4.png");
    }

    {
        sil::Image image{300, 200}; 
        exo5(image);
        image.save("output/exo5.png");
    }

    {
        sil::Image image{"images/logo.png"}; 
        exo6(image);
        image.save("output/exo6.png");
    }

    {
        sil::Image image{"images/logo.png"}; 
        exo7(image);
        image.save("output/exo7.png");
    }

    {
        sil::Image image{"images/logo.png"}; 
        exo8(image);
        image.save("output/exo8.png");
    }

    {
        sil::Image image{"images/logo.png"}; 
        exo9(image);
        image.save("output/exo9.png");
    }

    {
        sil::Image image{"images/photo.jpg"};
        exo10(image, 0.5f);
        image.save("output/exo10_light.png");
    }

    {
        sil::Image image{"images/photo.jpg"};
        exo10(image, 2.f);
        image.save("output/exo10_dark.png");
    }

    {
        sil::Image image{500, 500};
        exo11(image, 250, 250, 100);
        image.save("output/exo11.png");
    }

    {
        sil::Image image{500, 500};
        exo12(image, 250, 250, 150, 10);
        image.save("output/exo12.png");
    }

    {
        int total_frames = 30;
        for (int i{0}; i < total_frames; i++)
        {
            sil::Image image{500, 500};
            int center_x = (i * 500) / total_frames;
            exo11(image, center_x, 250, 50);
            image.save("output/exo13_" + std::to_string(i) + ".png");
        }
    }

    {
        sil::Image image{500, 500};
        exo14(image, 250, 250, 100, 3);
        image.save("output/exo14.png");
    }

    {
        sil::Image image{"images/logo.png"};
        exo15(image, 5, 5);
        image.save("output/exo15.png");
    }

    {
        sil::Image image{"images/logo.png"};
        exo17(image);
        image.save("output/exo17.png");
    }


}