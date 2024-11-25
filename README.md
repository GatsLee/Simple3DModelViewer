# Simple 3D Model Viewer

---

### Description

- This is a simple 3D Model Viewer that imports obj file and displays it in 3D space with OpenGL API
- This only use GLFW and GLEW library for window creation and OpenGL API
- Rest of the code is written from scratch: `Custom OBJ file parser, Custom Shader loader, Custom Camera controller, Custom Model loader, & Custom Math library`

### Features

- Import OBJ file
- Display 3D model in 3D space
- Rotate, Zoom, Pan the model
- Change model color

### How to use

- Clone the repository
- Open the project in Visual Studio
- Build the project
- Run the project

### Controls

- `WASD` : Move the camera(forward, left, backward, right)
- `Mouse Scroll` : Pan the camera
- `QE` : Move the camera up and down

### Screenshots

![Screenshot](https://github.com/GatsLee/Simple3DModelViewer/blob/master/ScreenShots/ScreenShot1.png)
![Screenshot](https://github.com/GatsLee/Simple3DModelViewer/blob/master/ScreenShots/ScreenShot2.png)

### Things to improve

- handle multiple textures in one model: currently only one texture is supported(will be updated soon)
- handle lighting(will be updated soon)
