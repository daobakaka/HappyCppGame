#pragma once
#include "Cube.h"
using namespace Game;


Cube::Cube(const char* vertexShaderSourceIn, const  char* fragmentShaderSourceIn) {
    
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSourceIn, nullptr);
    glCompileShader(vertexShader);
    CheckShaderCompilation(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSourceIn, nullptr);
    glCompileShader(fragmentShader);
    CheckShaderCompilation(fragmentShader);

    //这里就是传入两个shader  一个顶点 一个片元，然后对代码的两个shader 进行编译 glcompileShaer,后面一个自定义检查方法，检查shader编译是否成功，nullptr 
    //C风格的字符串以\0结尾,中间的数字1，代表字符串数组的资源数量 ，当前1个如果有多个则为const GLchar* sources[] = { source1, source2 }; glShaderSource(shader, 2, sources, nullptr);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    CheckShaderProgramLinking(shaderProgram);  // 检查着色器程序是否链接成功，这也是一个自定义的方法，这里代表将创建的shader 附加到项目中，并且链接到项目程序中

    glUseProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //这一步完成之后，就可以使用这个项目了，同时也可以删除顶点和片元着色器，
    
    // 
    // 
    // 创建和绑定VAO, VBO, EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    //绑定顶点缓冲数组
    //这里先生成图形所需要的 顶点数组 和缓冲buffer，包括顶点缓冲对象VBO，顶点数组对象VAO，元素缓冲对象 EBO

    // VBO: Vertex Buffer Object (顶点缓冲对象)
    glBindBuffer(GL_ARRAY_BUFFER, VBO);//GL_ARRAY_BUFFER 0x8892 数组缓冲对象是定义到固定的内存地址，绑定缓冲
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//GL_STATIC_DRAW 0x88E4   静态绘制区域

    // EBO: Element Buffer Object (元素缓冲对象)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);// GL_ELEMENT_ARRAY_BUFFER 0x8893  绑定元素缓冲对象，或者叫索引缓冲对象，储存数组的索引信息
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//GL_STATIC_DRAW 0x88E4   静态绘制区域

    //这里绘制需要的数据 都必须进入到 静态绘制区域才行，这样才能绘制，索引数组和顶点数组都在 cube.h的头文件中定义


    // 设置顶点属性指针，实际上就是告诉 OpenGL，缓冲区中存储的顶点属性数据包含 3 个浮点数 的位置信息，存储在每 3 个浮点数（有颜色则为6）的起始位置，且位置信息从偏移量 0 开始。
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);//这是启用顶点着色器中 layout(location = 0) 的属性数据。
    //----
    //告诉 OpenGL，缓冲区中存储的顶点属性数据包含 3 个浮点数 的颜色信息，存储在每 6 个浮点数 的偏移 3 开始的位置。
    glVertexAttribPointer(1, 3, GL_FLOAT, 0, 3 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);//这是启用顶点着色器中 layout(location = 1) 的属性数据
    //对应的两次参数,1个是顶点参数，第2个是片元的输入参数,宏的本质事实上是语义替换，增强了代码的可读性
    
    glBindVertexArray(0);  //1 解绑当前绑定的 VAO，防止后续对 VAO 的不必要修改 2 解绑后，VAO 的配置被保存在 GPU 中，后续只需重新绑定即可使用

    //-- //(GLAPIENTRY * PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
        //0 (GLuint index)

        //指定要配置的顶点属性的位置索引，对应顶点着色器中的 layout(location = 0)。
        //这个位置索引与着色器中声明的属性绑定。
        //3 (GLint size)

        //每个顶点属性的组件数量，这里为 3，表示顶点的 x, y, z 坐标。
        //GL_FLOAT(GLenum type)

        //指定顶点属性的数据类型，这里为 GL_FLOAT，表示每个组件是 32 位浮点数。
        //GL_FALSE(GLboolean normalized)

        //指定数据是否需要归一化。如果为 GL_TRUE，则数据会被映射到[0, 1] 或[-1, 1]。
        //这里为 GL_FALSE，表示不需要归一化，直接使用原始数据。
        //6 * sizeof(GLfloat) (GLsizei stride)

        //步幅（stride），表示两个连续顶点属性之间的间隔。
        //顶点属性由 x, y, z, r, g, b 六个分量组成，因此步幅为 6 * sizeof(GLfloat)。
        //(GLvoid*)0 (const void pointer) *

        //偏移量，表示数据在缓冲区中的起始位置。
        //这里为 0，表示顶点位置属性从数据的开头开始。
//--代码解读，与着色器对应

    //整体流程--1.创建shander 2.编译shader 3.创建shader项目 4 加载shader到shader项目并链接  3.将数据加载到帧缓冲区 4.告诉OPENGL/显卡， 帧缓冲区数据的绘制规则 5 解绑VAO，防止串改

}

 bool Cube::Draw(glm::mat4 view, glm::mat4 projection )//！继承的纯虚方法的实现，不用再加override关键字
 {

     size_t indicesLength = sizeof(indices) / sizeof(indices[0]);

     glUseProgram(shaderProgram);

     GLuint modelLoc = glGetUniformLocation(shaderProgram, "model");
     GLuint viewLoc = glGetUniformLocation(shaderProgram, "view");
     GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
     //这里是对 三个定义的 参数进行抓取，在shaderProgram 里面，这个参数是写在对应的shader里面进行定义的
     glUniformMatrix4fv(modelLoc, 1, 0, glm::value_ptr(transform));
     glUniformMatrix4fv(viewLoc, 1, 0, glm::value_ptr(view));
     glUniformMatrix4fv(projectionLoc, 1, 0, glm::value_ptr(projection));
     //这里的glm是一个常用的数学库，专门用与图形的矩阵操作，这里就充分诠释了 CPU之负责传输数据，GPU 来负责传输图形，
     // shader语言里面 使用 gl_Position = projection * view * model * vec4(aPos, 1.0f);进行渲染计算 
     glBindVertexArray(VAO);
     //绑定顶点数组对象（VAO），激活与 VAO 关联的顶点缓冲对象（VBO）和索引缓冲对象（EBO）。
     //保存顶点属性的配置，例如位置、颜色、法线、纹理坐标等，与 VBO 和 EBO 关联，用于存储顶点数据和绘制索引。
     glDrawElements(GL_TRIANGLES, indicesLength, GL_UNSIGNED_INT, 0);
     //索引数组存储在 EBO（Element Buffer Object）中，EBO 已绑定到 VAO，三角形，36个索引，无符号整形数组，由0开始
     glBindVertexArray(0);

     return true;
}

 bool Cube::DrawDynamical(glm::mat4 view, glm::mat4 projection)
 {
     return false;
 }


Cube::~Cube() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Cube::Update(glm::mat4 view, glm::mat4 projection)
{  

    //这种写法就，直接封装了更新变化和通知CPU渲染的两个方法，如果具体定义方法，只需要在其他脚本里面单独定义某个方法，更改transform即可，由管理池泛型调用
    UpdateTransform();
    Draw(view, projection);
}
//变体方法，可以增加变体的运行行为
void Cube::UpdateVariant(glm::mat4 view, glm::mat4 projection)
{
    scale = glm::vec3(2.0f, 2.0f, 2.0f);
    position += glm::vec3(0, 0, 0. - 0.01f);
   
}

bool Cube::AttachTexture(GLuint textureName, int order)
{
    return false;
}


