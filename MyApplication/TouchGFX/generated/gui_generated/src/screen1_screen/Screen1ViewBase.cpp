/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#include <gui_generated/screen1_screen/Screen1ViewBase.hpp>
#include <touchgfx/Color.hpp>
#include <images/BitmapDatabase.hpp>

Screen1ViewBase::Screen1ViewBase()
{
    __background.setPosition(0, 0, 240, 320);
    __background.setColor(touchgfx::Color::getColorFromRGB(0, 0, 0));
    add(__background);

    BackGround.setBitmap(touchgfx::Bitmap(BITMAP_EGG_BACKGROUND_ID));
    BackGround.setPosition(0, 0, 241, 320);
    BackGround.setOffset(0, 0);
    add(BackGround);

    Box.setPosition(0, 0, 240, 250);
    Celling.setBitmap(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_BACKGROUNDS_240X240_GRADIENT_DARK_ID));
    Celling.setPosition(-9, -7, 258, 18);
    Celling.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);
    Box.add(Celling);

    R_Wall.setBitmap(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_BACKGROUNDS_240X240_GRADIENT_DARK_ID));
    R_Wall.setPosition(230, 10, 15, 276);
    R_Wall.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);
    Box.add(R_Wall);

    L_Wall.setBitmap(touchgfx::Bitmap(BITMAP_ALTERNATE_THEME_IMAGES_BACKGROUNDS_240X240_GRADIENT_DARK_ID));
    L_Wall.setPosition(-5, 9, 15, 276);
    L_Wall.setScalingAlgorithm(touchgfx::ScalableImage::NEAREST_NEIGHBOR);
    Box.add(L_Wall);

    add(Box);

    Hitter.setPosition(0, 0, 240, 320);
    EggDirection.setXY(1, 0);
    EggDirection.setBitmap(touchgfx::Bitmap(BITMAP_ABC_ID));
    EggDirection.setWidth(240);
    EggDirection.setHeight(592);
    EggDirection.setBitmapPosition(117.5f, 183.5f);
    EggDirection.setScale(2.5f);
    EggDirection.setCameraDistance(1000.0f);
    EggDirection.setOrigo(120.0f, 296.0f, 1000.0f);
    EggDirection.setCamera(120.0f, 296.0f);
    EggDirection.setAngles(0.0f, 0.0f, 6.283f);
    EggDirection.setRenderingAlgorithm(touchgfx::TextureMapper::NEAREST_NEIGHBOR);
    Hitter.add(EggDirection);

    currentEgg.setXY(111, 286);
    currentEgg.setBitmap(touchgfx::Bitmap(BITMAP_GREEN_REMOVEBG_PREVIEW_ID));
    currentEgg.setVisible(false);
    Hitter.add(currentEgg);

    add(Hitter);

    Dumper.setPosition(-1, 0, 241, 320);
    YellowEgg.setXY(-29, 29);
    YellowEgg.setBitmap(touchgfx::Bitmap(BITMAP_YELLOW_REMOVEBG_PREVIEW_ID));
    Dumper.add(YellowEgg);

    GreenEgg.setXY(-29, 9);
    GreenEgg.setBitmap(touchgfx::Bitmap(BITMAP_GREEN_REMOVEBG_PREVIEW_ID));
    Dumper.add(GreenEgg);

    RedEgg.setXY(-29, -9);
    RedEgg.setBitmap(touchgfx::Bitmap(BITMAP_RED_REMOVEBG_PREVIEW_ID));
    Dumper.add(RedEgg);

    TestingEgg.setXY(-29, 49);
    TestingEgg.setBitmap(touchgfx::Bitmap(BITMAP_RED_REMOVEBG_PREVIEW_ID));
    Dumper.add(TestingEgg);

    add(Dumper);

    image1.setXY(1, 249);
    image1.setBitmap(touchgfx::Bitmap(BITMAP_EGG_PURPLE_ID));
    add(image1);
}

Screen1ViewBase::~Screen1ViewBase()
{

}

void Screen1ViewBase::setupScreen()
{

}
