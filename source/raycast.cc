#include "raycast.h"
#include <stdio.h>

// Globals:

// File names
char *_inputName       = NULL;
char *_outputNameRGB   = NULL;
char *_outputNameDepth = NULL;

// Image parameters.
int _width      = 100;
int _height     = 100;
float _depthMin = 0;
float _depthMax = 1;

// Render a color image of objects in a scene.
void renderRGBImage(SceneParser &, Image &);

// Render an image showing the depth of objects from the camera.
void renderDepthImage(SceneParser &, Image &);

int main(int argc, char** argv) {

  int i;
  // sample command lines:
  // raycast -input input.txt -size 100 100 -output output.ppm
  // raycast -input input.txt -size 100 100 -depth 5.5 8.8 output.ppm

  for (i = 1; i < argc; i++) {
    if (strcmp(argv[i], "-input") == 0) {
      i++;assert (i < argc);
      _inputName = argv[i];
    } else if (strcmp(argv[i], "-size") == 0) {
      i++;assert (i < argc);
      _width = atoi(argv[i]);
      i++;assert (i < argc);
      _height = atoi(argv[i]);
    } else if (strcmp(argv[i], "-output") == 0) {
      i++;assert (i < argc);
      _outputNameRGB = argv[i];
    } else if (strcmp(argv[i], "-depth") == 0) {
      i++;assert (i < argc);
      _depthMin = atof(argv[i]);
      i++;assert (i < argc);
      _depthMax = atof(argv[i]);
      i++;assert (i < argc);
      _outputNameDepth = argv[i];
    } else {
      printf(
          "Error with command line argument %d: '%s'\n",
          i, argv[i]);
      assert(0);
    }
  }

  // Read in the scene description file, parsing the objects,
  // camera details, etc.
  SceneParser scene(_inputName);

  // Color and depth images.
  Image rgbImage(_width, _height);
  Image depthImage(_width, _height);

  // Do the rendering.
  renderRGBImage(scene, rgbImage);
  renderDepthImage(scene, depthImage);

  // Write results if necessary.
  if (_outputNameRGB != NULL) {
    rgbImage.SavePPM(_outputNameRGB);
  }

  if (_outputNameDepth != NULL){
    depthImage.SavePPM(_outputNameDepth);
  }

}

// Render a color image of objects in a scene.
void renderRGBImage(SceneParser &scene, Image &image) {
  Group *group = scene.getGroup();
  Camera *camera = scene.getCamera();
  Vec3f background = scene.getBackgroundColor();
  Hit *hit = new Hit(INFINITY, background);
  
  float i;
  float j;
  for (i = 0; i < image.Width(); i++){
      for (j = 0; j < image.Height(); j++) {
          hit->set(INFINITY, background);
          Vec2f point = Vec2f(i / image.Width(), j / image.Height());
          Ray ray = camera->generateRay(point);
          if (group->intersect(ray, *hit)){
            image.SetPixel(i, j, hit->getColor());
          } else {
            image.SetPixel(i, j, background);
          }
      }
  }

}

// Render an image showing the depth of objects from the camera.
void renderDepthImage(SceneParser &scene, Image &image) {
  Group *group = scene.getGroup();
  Camera *camera = scene.getCamera();
  Vec3f background = scene.getBackgroundColor();
  Hit *hit = new Hit(INFINITY, background);
  
  float i;
  float j;
  for (i = 0; i < image.Width(); i++){
      for (j = 0; j < image.Height(); j++) {
          hit->set(INFINITY, background);
          Vec2f point = Vec2f(i / image.Width(), j / image.Height());
          Ray ray = camera->generateRay(point);
          if (group->intersect(ray, *hit) && hit->getT() <= _depthMax && 
                  hit->getT() >= _depthMin) {
            float grey_val = 1 - (hit->getT() - _depthMin) / (_depthMax - _depthMin);
            image.SetPixel(i, j, Vec3f(grey_val, grey_val, grey_val));
          } else {
            image.SetPixel(i, j, Vec3f(0,0,0));
          }
      }
  }
}

