// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <vector>
#include <memory>
using namespace std;

// TODO: 在此处引用程序需要的其他头文件
#include "glad/glad.h"
#include "glfw/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Common/TypeDef.h"
#include "Common/common.h"
#include "Common/CShader.h"
#include "Common/CCamera.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Common/stb_image.h"