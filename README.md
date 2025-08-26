
# OpenGL Playground

Welcome to my OpenGL Playground! This project is my personal space for learning and experimenting with various OpenGL concepts and techniques. Every line of code here documents my journey of exploring the world of 3D graphics from scratch.

![Project Screenshot](./opengl_playground/res/shadowmapping.png?raw=true)

## Purpose of the Project

The main goal of this repository is to serve as a dynamic learning diary and a code laboratory. By getting my hands dirty, I transform theoretical knowledge into visible 3D scenes, thereby gaining a deeper understanding of the underlying principles of computer graphics. If you are also a learner of OpenGL, I hope this project can provide you with some inspiration and reference.

## Features Explored So Far

*   **Basic Scene Setup:** Learned how to create basic 3D objects using VBOs, VAOs, and EBOs.
*   **Shaders:** Wrote GLSL shaders by hand to implement effects like lighting, color, and textures.
*   **Camera System:** Implemented a first-person camera that can move and look around freely in the scene.
*   **Lighting Model:** Implemented the basic Phong lighting model to give objects a sense of volume.
*   **Model Loading:** Learned how to load external 3D models using the Assimp library.
*   **Texture Mapping:** Applied textures to 3D models to make them look more realistic.
*   **Shadow Mapping:** Implemented a basic shadow technique to make the lighting in the scene more convincing.

## Getting Started

### Prerequisites

*   **Visual Studio 2022:** It is recommended to use Visual Studio 2022 to compile and run this project.
*   **Dependencies:** All required libraries (GLEW, GLFW, GLM, Assimp) are already included in the `opengl_playground/dependency` folder, so no additional downloads are necessary.

### How to Build and Run

1.  **Open the Solution:** Open the `opengl_playground/opengl_playground.sln` file with Visual Studio 2022.
2.  **Select Configuration:** In the toolbar, select the `Release` and `x64` configuration.
3.  **Build the Project:** Press `Ctrl+Shift+B` or click on `Build > Build Solution` from the menu to compile the project.
4.  **Run the Application:** After a successful build, you can press `F5` to run it directly from Visual Studio, or find and run `opengl_playground.exe` in the `opengl_playground/x64/Release/` directory.


---

I hope you enjoy this project! If you have any suggestions or questions, feel free to raise an issue.
