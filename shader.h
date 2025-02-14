#ifndef SHADERS_Hero
#define SHADERS_Hero
//����shader ����ֻ�ܱ�һ���ļ����ã��������ļ���ʹ������Ҫʹ������ extern ����������

/// <summary>
/// ������ɫ��
/// </summary>
const char* cubeVertexShaderSource = R"(
    #version 450 core
    layout (location = 0) in vec3 aPos;   // ����λ��
    out vec3 ourColor;                    // ���ݸ�Ƭ����ɫ������ɫ
    uniform mat4 model;                   // ģ�ͱ任����
    uniform mat4 view;                    // ��ͼ�任����
    uniform mat4 projection;              // ͶӰ����
    uniform vec3 color;                   // ��ɫ (ͨ�� uniform ����)
    
    void main() {
        gl_Position = projection * view * model * vec4(aPos, 1.0f);
        ourColor = color;  // ����ɫ���ݸ�Ƭ����ɫ��
    }
)";

const char* cubeFragmentShaderSource = R"(
    #version 450 core
    out vec4 FragColor;  // �����ɫ
    in vec3 ourColor;    // �Ӷ�����ɫ�����ݹ�������ɫ
    
    void main() {
        // Ĭ��ǳ��ɫ������͸����
        vec3 defaultColor = vec3(1.0f, 1.0f, 1.0f);  // ����ɫ
        FragColor = vec4(ourColor+defaultColor, 0.5f);  // ʹ�ô��ݵ���ɫ��������͸����
    }
)";
/// <summary>
/// �ο���������ת��ɫ��
/// </summary>
const char* axisVertexShaderSource = R"(
    #version 450 core
layout (location = 0) in vec3 aPos;     // ����λ��
layout (location = 1) in vec3 aColor;   // ������ɫ
out vec3 ourColor;                      // �����ƬԪ��ɫ������ɫ

uniform mat4 model;       // ģ�ͱ任����
uniform mat4 view;        // ��ͼ����
uniform mat4 projection;  // ͶӰ����

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    ourColor = aColor;
}

)";
const char* axisFragmentShaderSource = R"(
    #version 450 core
    in vec3 ourColor;       // �Ӷ�����ɫ���������ɫ
    out vec4 FragColor;     // �����ƬԪ��ɫ

    void main() {
        FragColor = vec4(ourColor, 1.0);
    }
)";



/// <summary>
/// ������ɫ��
/// </summary>
const char* rayVertexShaderSource = R"(
#version 450 core
layout (location = 0) in vec3 aPos;  // ����λ��

uniform mat4 model;       // ģ�ͱ任����
uniform mat4 view;        // ��ͼ����
uniform mat4 projection;  // ͶӰ����

void main()
{
    // ��׼ MVP �任
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)";
const char* rayFragmentShaderSource = R"(
#version 450 core
out vec4 FragColor;

// ������ɫ�� baseColor ���ƣ����δ����Ĭ��(0.1,0.1,0.1)
uniform vec3 baseColor;

void main()
{
    // ��� baseColor == vec3(0.0), Ĭ����(0.1,0.1,0.1)
    vec3 colorUsed = (baseColor == vec3(0.0)) ? vec3(1, 1, 1) : baseColor;
    
    FragColor = vec4(colorUsed, 1.0);
}
)";
/// <summary>
/// ����������ɫ��
/// </summary>
const char* lightSourceVertexShaderSource = R"(
    #version 450 core
    layout (location = 0) in vec3 aPos;   // ����λ��
    out vec3 fragPos;                     // ���ݸ�Ƭ����ɫ���Ķ���λ��
    uniform mat4 model;                   // ģ�ͱ任����
    uniform mat4 view;                    // ��ͼ�任����
    uniform mat4 projection;              // ͶӰ����
    
    void main() {
        fragPos = vec3(model * vec4(aPos, 1.0f));  // ����任��Ķ���λ��
        gl_Position = projection * view * model * vec4(aPos, 1.0f);  // ��������λ��
    }
)";

const char* lightSourceFragmentShaderSource = R"(
    #version 450 core
    out vec4 FragColor;  // �����ɫ
    in vec3 fragPos;    // �Ӷ�����ɫ�����ݹ����Ķ���λ��,������ʵ�ϣ��������������������λ��

    // ��Դ����
    uniform vec3 lightPos;      // ��Դλ��,uniform �����ȫ�ֵĶ���
    uniform vec3 lightColor;    // ��Դ��ɫ
    uniform float lightIntensity; // ��Դǿ��
    uniform vec3 viewPos;        // �ӵ�λ��
    uniform vec3 baseColor;//����ɫ
    uniform vec3 emission;//�Է��⣬ͨ���ӵ���ɫ�����ĩβ

    void main() {
        // �Է��⣨Emission��
       vec3 emissionDefault=(emission == vec3(0.0f,0.0f,0.0f))?vec3(0.1f,0.1f,0.1f):emission;  // ����ɫ�Է���
       vec3 colorToUse = (baseColor == vec3(0.0f,0.0f,0.0f))?vec3(0.3f, 0.3f, 0.0f):baseColor;      
        // ���ղ���
        // ������
        vec3 ambient = 0.1 * lightColor;  //�������˥���������⡢�����䡢���淴���ͨ��ʹ�ó˷����˷�ͨ�������ģ�����˥��Ч��

        // �����Դλ�ú�������淨��֮��ĽǶ� 
        vec3 lightDir = normalize(lightPos - fragPos);  
        float diff = max(dot(normalize(fragPos), lightDir), 0.0);  // ������
        vec3 diffuse = diff * lightColor * lightIntensity;  // ���������

        // ���淴��
        vec3 reflectDir = reflect(-lightDir, normalize(fragPos));  // ��������
        vec3 viewDir = normalize(viewPos - fragPos);  // �����嵽�ӵ������
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);  // ���淴��
        vec3 specular = spec * lightColor * lightIntensity*0.1f;

        // �ϲ����й��ճɷ�
        vec3 result = (ambient + diffuse + specular);

        // ������ɫ = �Է��� + ����Ч��
        FragColor = vec4(result + emissionDefault + colorToUse, 0.5f);  // ʹ�ù��ս�����Է�����
    }
)";
/// <summary>
/// ����������ɫ������ɫ��
/// </summary>
const char* colorlightSourceVertexShaderSource = R"(
  #version 450 core

layout (location = 0) in vec3 aPos;      // ����λ��
layout (location = 1) in vec3 aNormal;   // ���㷨��

out vec3 fragPos;   // ����ռ�����
out vec3 Normal;    // ����ռ䷨��

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // ��������ռ�����
    vec4 worldPos = model * vec4(aPos, 1.0);
    fragPos = worldPos.xyz;

    // ��� model �����Ǿ������ţ���ĳ�:
    // Normal = mat3(transpose(inverse(model))) * aNormal;
    // ����ֻ����ʾ, ���� model �����Ǿ�������:
    Normal = mat3(model) * aNormal;

    // ����λ��
    gl_Position = projection * view * worldPos;
}

)";

const char* colorlightSourceFragmentShaderSource = R"(
#version 450 core

in vec3 fragPos;  
in vec3 Normal;
out vec4 FragColor;

// uniform: ����Ĺ��ա���������ʵȲ���
uniform vec3 lightPos;
uniform vec3 lightColor;
uniform float lightIntensity;
uniform vec3 viewPos;
uniform vec3 baseColor;   // ���Ե���ģ�͵Ĺ���ɫ
uniform vec3 emission;    // �Է��⣨��ѡ��

void main()
{
    // �Է���Ĭ��ֵ(��ѡ�߼�)
    vec3 emissionDefault = (emission == vec3(0.0)) ? vec3(0.1) : emission;

    // ��� baseColor û���ã�Ĭ�ϸ�һ�������ɫ
    vec3 colorToUse = (baseColor == vec3(0.0)) ? vec3(0.1, 0.1, 0.1) : baseColor;

    // 1. ������
    vec3 ambient = 0.1 * lightColor;

    // 2. ������
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor * lightIntensity;

    // 3. ���淴��(Phong)
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = spec * lightColor * lightIntensity * 0.1;

    // �ϲ�
    vec3 lighting = ambient + diffuse + specular;

    // ������ɫ = (���� �� �������ɫ) + �Է���
    vec3 result = lighting * colorToUse + emissionDefault;
    FragColor = vec4(result, 1.0);
}
)";
/// <summary>
/// ��ɫ����ͨ����ɫ��
/// </summary>
const char* colorlightsArrayVertexShaderSource = R"(
#version 450 core
layout(location = 0) in vec3 aPos;       // ����λ��
layout(location = 1) in vec2 aTexCoord;    // ��������
layout(location = 2) in vec3 aNormal;      // ���㷨��

// �����Ƭ����ɫ��
out vec2 TexCoord;   // ������������
out vec3 FragPos;    // ����ռ��е�Ƭ��λ��
out vec3 Normal;     // ����ռ��еķ���

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // ��������ռ�����
    vec4 worldPos = model * vec4(aPos, 1.0);
    FragPos = worldPos.xyz;

    // ������������
    TexCoord = aTexCoord;

    // ��ȷ�任���ߣ���ֹ�Ǿ�����������
    Normal = mat3(transpose(inverse(model))) * aNormal;

    // ����������Ļ����
    gl_Position = projection * view * worldPos;
}
)";




const char* colorlightsArraySourceFragmentShaderSource = R"(
#version 450 core

in vec3 FragPos;  
in vec3 Normal;
in vec2 TexCoord;  // ������������
out vec4 FragColor;

//
// ���Դ����
//
const int MAX_POINT_LIGHTS = 4;
uniform vec3 lightPos[MAX_POINT_LIGHTS];
uniform vec3 lightColor[MAX_POINT_LIGHTS];
uniform float lightIntensity[MAX_POINT_LIGHTS];

//
// ƽ�й⣨����⣩����
//
uniform vec3 parallelLightDirection; // ���ߴ�������ͨ��Ϊ�ӹ�Դָ�򳡾����򣬿ɸ�����Ҫȡ����
uniform vec3 parallelLightColor;
uniform float parallelLightIntensity;

//
// �ֵ�Ͳ���۹�ƣ�����
//
const int MAX_FLASHLIGHTS = 4;
uniform vec3 flashLightPos[MAX_FLASHLIGHTS];
uniform vec3 flashLightDirection[MAX_FLASHLIGHTS];
uniform vec3 flashLightColor[MAX_FLASHLIGHTS];
uniform float flashLightIntensity[MAX_FLASHLIGHTS];
uniform float flashLightCutoff[MAX_FLASHLIGHTS]; // cutoff ֵΪ����ֵ

//
// ��������
//
uniform vec3 viewPos;
uniform vec3 baseColor;   // ģ�͹���ɫ
uniform vec3 emission;    // �Է��⣨��ѡ��
uniform sampler2D texture1;  // ���������

void main()
{
    // �Է���Ĭ��ֵ(��ѡ�߼�)
    vec3 emissionDefault = (emission == vec3(0.0)) ? vec3(0.1) : emission;

    // ��� baseColor û���ã�Ĭ�ϸ�һ�������ɫ
    vec3 colorToUse = (baseColor == vec3(0.0)) ? vec3(0.1, 0.1, 0.1) : baseColor;

    vec3 norm = normalize(Normal);

    vec3 ambientTotal = vec3(0.0);
    vec3 diffuseTotal = vec3(0.0);
    vec3 specularTotal = vec3(0.0);
    
    // --- ���Դ���� ---
    for (int i = 0; i < MAX_POINT_LIGHTS; i++) {
        if (lightIntensity[i] > 0.0001) {
            // �����⣺ÿ�����Դ������ 10%
            ambientTotal += 0.1 * lightColor[i];
            
            // ������
            vec3 lightDir = normalize(lightPos[i] - FragPos);
            float diff = max(dot(norm, lightDir), 0.0);
            diffuseTotal += diff * lightColor[i] * lightIntensity[i];
            
            // ���淴�䣨Phong ģ�ͣ�
            vec3 viewDir = normalize(viewPos - FragPos);
            vec3 reflectDir = reflect(-lightDir, norm);
            float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
            specularTotal += spec * lightColor[i] * lightIntensity[i] * 0.1;
        }
    }
    
    // --- ƽ�й⣨����⣩���� ---
    if (parallelLightIntensity > 0.0001) {
        // �����⹱��
        ambientTotal += 0.1 * parallelLightColor;
        
        // ���ڷ���⣬������߷���Ϊ parallelLightDirection�������Ҫ�ӹ�Դָ�򳡾�����ʹ�� -parallelLightDirection��
        vec3 lightDir = normalize(-parallelLightDirection);
        float diff = max(dot(norm, lightDir), 0.0);
        diffuseTotal += diff * parallelLightColor * parallelLightIntensity;
        
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
        specularTotal += spec * parallelLightColor * parallelLightIntensity * 0.1;
    }
    
    // --- �ֵ�Ͳ���۹�ƣ����� ---
    for (int j = 0; j < MAX_FLASHLIGHTS; j++) {
        if (flashLightIntensity[j] > 0.0001) {
            ambientTotal += 0.1 * flashLightColor[j];
            
            vec3 lightDir = normalize(flashLightPos[j] - FragPos);
            // ����۹�Ч����ʹ�ù������ֵ�Ͳ����ĵ��
            float theta = dot(lightDir, normalize(flashLightDirection[j]));
            // ֻ�е� theta ���� cutoff ʱ��������Ч
            if (theta > flashLightCutoff[j]) {
                float diff = max(dot(norm, lightDir), 0.0);
                diffuseTotal += diff * flashLightColor[j] * flashLightIntensity[j];
                
                vec3 viewDir = normalize(viewPos - FragPos);
                vec3 reflectDir = reflect(-lightDir, norm);
                float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
                specularTotal += spec * flashLightColor[j] * flashLightIntensity[j] * 0.1;
            }
        }
    }
    
    vec3 lighting = ambientTotal + diffuseTotal + specularTotal;
    
    // ������ɫ = (����Ч�� �� �������ɫ) + �Է���
    vec3 result = lighting * colorToUse + emissionDefault;
    
    // ����������ɫ��������ս�����
    vec4 texColor = texture(texture1, TexCoord);
    FragColor = vec4(result, 1.0) * texColor;
}
)";


/// <summary>
/// �޹���ͨ����ɫ��
/// </summary>

const char* noneLightVertexShaderSource = R"(
#version 450 core
layout(location = 0) in vec3 aPos;   // ����λ��
layout(location = 1) in vec2 aTexCoord;   // �������� 
layout(location = 2) in vec3 aNormal;   // ����
//�����Ӧ��ʼ��ʱ�����õĶ�������
out vec2 TexCoord;  // ���ݸ�Ƭ����ɫ������������
out vec3 FragPos;   // ���ݸ�Ƭ����ɫ����Ƭ��λ��

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    TexCoord = aTexCoord;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)";

const char* noneLightFragmentShaderSource = R"(
#version 450 core

out vec4 FragColor;

in vec2 TexCoord;   // �Ӷ�����ɫ�����յ���������
in vec3 FragPos;    // �Ӷ�����ɫ�����յ�Ƭ��λ��

uniform vec3 baseColor;      // ���Ե���ģ�͵Ĺ���ɫ
uniform sampler2D texture1;  // ����

void main()
{
    // ��� baseColor == (0,0,0)����Ĭ��ʹ��(0.1, 0.1, 0.1)
    // ע�⣺���������� == �Ƚ��� GLSL 4.5 ��������ģ������Ҫ�ж��Ƿ����Ϊ�㣬���Ը��� length(baseColor) < 1e-6 �ȡ�
    vec3 colorToUse = (baseColor == vec3(0.0)) ? vec3(0.1, 0.1, 0.1) : baseColor;

    // ����� baseColor �ӵ�������ɫ���ɸ�Ϊ�˷�����
    FragColor = (texture(texture1, TexCoord) + vec4(colorToUse, 1.0)) ;
} 
)";
/// <summary>
/// �޹��չ�Դ��Ⱦ��ɫ��
/// </summary>
const char* noneLightLightVertexShaderSource = R"(
#version 450 core
layout(location = 0) in vec3 aPos;   // ����λ��
layout(location = 1) in vec2 aTexCoord;   // �������� 
layout(location = 2) in vec3 aNormal;   // ����
//�����Ӧ��ʼ��ʱ�����õĶ�������
out vec2 TexCoord;  // ���ݸ�Ƭ����ɫ������������
out vec3 FragPos;   // ���ݸ�Ƭ����ɫ����Ƭ��λ��

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    TexCoord = aTexCoord;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)";

const char* noneLightLightFragmentShaderSource = R"(
#version 450 core

out vec4 FragColor;

in vec2 TexCoord;   // �Ӷ�����ɫ�����յ���������
in vec3 FragPos;    // �Ӷ�����ɫ�����յ�Ƭ��λ��

uniform vec3 baseColor;      // ���Ե���ģ�͵Ĺ���ɫ
uniform sampler2D texture1;  // ����
uniform float lightIntensity; // ��ǿ�ȿ��ӻ�
uniform float lightDirection;//���շ�����ʱ����
void main()
{
    // ��� baseColor == (0,0,0)����Ĭ��ʹ��(0.1, 0.1, 0.1)
    // ע�⣺���������� == �Ƚ��� GLSL 4.5 ��������ģ������Ҫ�ж��Ƿ����Ϊ�㣬���Ը��� length(baseColor) < 1e-6 �ȡ�
    vec3 colorToUse = (baseColor == vec3(0.0)) ? vec3(0.1, 0.1, 0.1) : baseColor;

    // ��� lightIntensity==0����Ĭ��ֵΪ0.1
    float tempIntensity = (lightIntensity == 0.0) ? 0.1f : lightIntensity;

    // ����ȡ�� + baseColor���ٳ��Թ�ǿ��
    // ����� baseColor �ӵ�������ɫ���ɸ�Ϊ�˷�����
    FragColor = (texture(texture1, TexCoord) *vec4(colorToUse, 1.0))* 0.5f* tempIntensity;
} 
)";


/// <summary>
/// ������Ⱦ��ɫ��
/// </summary>
const char* textRenderVertex = R"(
#version 450 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;
out vec2 TexCoordText;
uniform mat4 projection;  // ��������
void main()
{
    gl_Position = projection * vec4(aPos, 1.0, 1.0);  // Ӧ������ͶӰ������ZֵΪ1 �ǰ��opengl ��Zֵ��ΧΪ[-1,1],��Զ����
    TexCoordText = aTexCoord;
}
)";

const char* textRenderFragment = R"(

#version 450 core
in vec2 TexCoordText;  // �Ӷ�����ɫ����������������
out vec4 FragColor; // ������ɫ���
uniform sampler2D text; // ��������
uniform vec3 textColor; // �ı���ɫ
void main()
{
    vec4 sampled = texture(text, TexCoordText);  // ��ȡ������ɫ
    if (sampled.r == 0)  // ���ɫ����0������Ⱦ
        discard;
   /* else
        sampled.r=1;*/
    FragColor = vec4(textColor,1)*sampled.r;
       // FragColor = vec4(textColor * sampled.r, 1);  // ���Ժ�ɫͨ���ĻҶ�ֵ
       // FragColor = vec4(textColor,1.0f)*sampled;
}
)";


#endif