#if OBSOLETE_CODE_KAKA

//�����ʼ������
       //����ģ������
       // Load OBJ file
std::vector<glm::vec3> vertices;
std::vector<glm::vec2> uvs;
std::vector<glm::vec3> normals;
std::vector <unsigned int> indeies;
bool res = LoadOBJ("E:\\C++\\FirstOne\\C++Steam52\\Assests\\Obj\\butterfly2.obj", vertices, uvs, normals);
if (!res) {
    std::cerr << "Failed to load OBJ file!" << std::endl;
    return -1;
}
std::vector<Vertex> verticesStruct;
std::vector<unsigned int> indices;
if (!LoadOBJ("E:\\C++\\FirstOne\\C++Steam52\\Assests\\Obj\\butterfly1.obj", verticesStruct, indices)) {
    DEBUGLOG("Faild to load obj verteices only");
}
//��ѹͼƬ��ϢΪ���ø�ʽ
// ��������
GLuint picTexture = LoadPicTexture("E:\\C++\\FirstOne\\C++Steam52\\Assests\\Texture\\1.png");
if (picTexture == 0)
{
    // �������ʧ�ܵ����
    std::cerr << "Texture loading failed." << std::endl;
    // ������Ҫ�˳�������ȡ������ʩ
}
//���ֵ��뷽ʽ���ɣ��ڶ���Ч�ʸ��ߣ���Ҫԭ������û�п������ǻ�������ȫ���ı��Σ���ɻ����ο�      
// printVectors(vertices, uvs, normals);
CustomModel* LDmodel = new CustomModel(noneLightVertexShaderSource, noneLightcubeFragmentShaderSource, verticesStruct, indices, true);//������ǵ�ַ��Ҳ���Ǵ������ã����ַ�ʽ������ref
manager->RegisterObject(LDmodel);
LDmodel->Initialize(glm::vec3(2.0f, 0.0f, 1.0f), glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
GLuint picData = glGetUniformLocation(LDmodel->shaderProgram, "texture1");

//--
     // Load OBJ file
std::vector<Vertex> verticesStruct;
std::vector<unsigned int> indices;
if (!LoadOBJ("E:\\C++\\FirstOne\\C++Steam52\\Assests\\Obj\\butterfly1.obj", verticesStruct, indices)) {
    DEBUGLOG("Faild to load obj verteices only");
}


CustomModel* LDmodel = new CustomModel(noneLightVertexShaderSource, noneLightcubeFragmentShaderSource, ModelDic["butterfly"].verticesStruct, ModelDic["butterfly"].indices, true);//������ǵ�ַ��Ҳ���Ǵ������ã����ַ�ʽ������ref
///--��������
GLuint picTexture = LoadPicTexture("E:\\C++\\FirstOne\\C++Steam52\\Assests\\Texture\\1.png");


// ���������������Ƿ�ѭ�����ţ������ٶȣ����ö��������γɵĶ��������ļ�
Animation* anim = new Animation(AnimationDic["butterfly"]["fly"]);
// ��������������
AnimationController* animator = new AnimationController();
// ��������ӵ���������
animator->AddAnimation(anim);


//����󶨷���
  // ʹ����ɫ������
//glUseProgram(LDmodel->shaderProgram);
//glActiveTexture(GL_TEXTURE0);          // ��������Ԫ 0
//glBindTexture(GL_TEXTURE_2D, TextureDic["butterfly"][0]);  // �������������Ԫ 0,�������"butterfly"���ϵ��������
//// ����������Ԫ 0
//glUniform1i(picData, 0);
//--����ģ��
// LDmodel->UpdateVerticesForAnimation(10);//���α����Ч��
 //��������,����������ֱ�ӿ��ƶ������������ָ��
 // animator->PlayAnimation(0,0.03f,LDmodel);


//--OPENGL ������Ⱦ��ʽ

       // 1. ���浱ǰ�� OpenGL ״̬
        GLint previousShader;
        glGetIntegerv(GL_CURRENT_PROGRAM, &previousShader);  // ��ȡ��ǰ����

        GLint previousTexture;
        glGetIntegerv(GL_TEXTURE_BINDING_2D, &previousTexture);  // ��ȡ��ǰ�󶨵�����

        // 2. ��Ⱦ����
        cusText->RenderText("Hello World", 100.0f, 100.0f, 10.0f, glm::vec3(1.0f, 1.0f, 1.0f));

        // 3. �ָ�֮ǰ�� OpenGL ״̬
        glUseProgram(previousShader);  // �ָ�֮ǰ����ɫ��
        glBindTexture(GL_TEXTURE_2D, previousTexture);  // �ָ�֮ǰ�������



        //  Cube* newCube1 = new Cube(cubeVertexShaderSource, cubeFragmentShaderSource);//��������ʵ�ֲ����滻
// newCube1->Initialize(glm::vec3(2.0f, 0.0f, 0.0f), glm::quat(glm::vec3(0.0f, 45.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));
//// newCube1->SetVariant(ModelClass::CubeE);
// manager->RegisterObject(newCube1);
// scripts->TChangeRandom(-0.01f, 0.01f);//�ı乹���������

 Cube* newCube2 = new Cube(cubeVertexShaderSource, cubeFragmentShaderSource);//��������ʵ�ֲ����滻
 newCube2->Initialize(glm::vec3(.0f, 0.0f, 0.0f), glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)), glm::vec3(0.1f, 0.10f, .10f));
 // newCube1->SetVariant(ModelClass::CubeE);
 manager->RegisterObject(newCube2);
 // std::list<Cube*> cubes;  // ʹ�� std::list �洢 Cube ����ָ��//�ۺϽű���������
 for (int i = 0; i < 0; i++)
 {
     Cube* newCubeClone = new Cube(cubeVertexShaderSource, cubeFragmentShaderSource);
     float random = scripts->TGetRandomFloat(-1.0f, 1.0f);
     newCubeClone->Initialize(glm::vec3(random, random, random), glm::quat(glm::vec3(random * 5, random * 10, random * 10)), glm::vec3(0.8f, 0.8f, 0.8f));
     manager->RegisterObject(newCubeClone);//����������ע����
 }

 for (int i = 0; i < 0; i++)
 {
     Cube* newCubeClone = new Cube(cubeVertexShaderSource, cubeFragmentShaderSource);
     float random = scripts->TGetRandomFloat(-1.0f, 1.0f);
     newCubeClone->Initialize(glm::vec3(random, random, random), glm::quat(glm::vec3(random * 5, random * 10, random * 10)), glm::vec3(1.5f, 1.5f, 1.5f));
     newCubeClone->SetVariant(ModelClass::CubeE);
     manager->RegisterObject(newCubeClone);
 }
//---���ｫGanmeObject ����������������ƶ���ת��ΪCustomModel �࣬����һ���Ϳ���ִ���µĶ����˶���ģʽ������֮ǰ��GameObject ����
//---  �����������������ԭʼ����
        for (int i = 0; i < 30; i++)
        {
            CustomModel* LDmodel = new CustomModel(noneLightVertexShaderSource, noneLightcubeFragmentShaderSource, ModelDic["butterfly"], true);//������ǵ�ַ��Ҳ���Ǵ������ã����ַ�ʽ������ref
            manager->RegisterObject(LDmodel);
            LDmodel->Initialize(glm::vec3(2.0f, 0.0f, i * 0.5f), glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)), glm::vec3(0.1f, 0.1f, 0.1f));
            //--ģ�͸��Ӳ������   
            LDmodel->AttachTexture();
            //--ģ�͸�������������
            LDmodel->AttachAnimationController(AnimationDic["butterfly"]["fly"]);//���ﴫ��һ��Ĭ�ϲ���������֪������Ķ������ƺ��׶���
            LDmodel->AttachPhysicalEngine();
            LDmodel->AttachCollider();
            auto* aa = LDmodel->GetComponent<AnimationController>();
            DEBUGLOG(aa);
            //��ʼ������          
            LDmodel->SetVariant(ModelClass::ActorButterfly);
        }

        //--��ʼ�ĵƹⶨ�巽ʽ
        CustomPointLight pointLight;
        pointLight.position = glm::vec3(0.0f, 0.0f, 0.0f);
        pointLight.color = glm::vec3(1.0f, .0f, .0f);
        pointLight.intensity = 5.0f;

        GLuint lightshader = customCone->shaderProgram;
        GLuint lightPosLoc = glGetUniformLocation(lightshader, "lightPos");//��ȡshader�е���صĲ�����������������������ã���Ϊ����һ��shader ���Ըı�һ�����ڸı�ȫ��
        GLuint lightColorLoc = glGetUniformLocation(lightshader, "lightColor");
        GLuint lightIntensityLoc = glGetUniformLocation(lightshader, "lightIntensity");

// -- ���Դ��Ⱦ���ƴ���

         else if (item->GetVariant() == ModelClass::TsetButterfly)
         {

             //����Ҳ����ִ�б��巽������������֤
             item->UpdateVariant(view, projection);
             item->PlayAnimation(0, 0.1f);



             //--
             // ʹ�ø������ shader ����
             glUseProgram(item->shaderProgram);

             // ������������ݣ������� controller->front ��ʾ�����ǰ���λ�����ݣ��ɸ���ʵ������滻��
             GLuint viewPosLoc = glGetUniformLocation(item->shaderProgram, "viewPos");
             glm::vec3 viewP = glm::vec3(controller->front);
             glUniform3f(viewPosLoc, viewP.x, viewP.y, viewP.z);


             // ������Դ����
             auto pointLights = lightController->GetPointLights();
             for (int i = 0; i < MAX_LIGHTS; i++)
             {
                 // ƴ�� uniform ��������
                 std::string posName = "lightPos[" + std::to_string(i) + "]";
                 std::string colorName = "lightColor[" + std::to_string(i) + "]";
                 std::string intensityName = "lightIntensity[" + std::to_string(i) + "]";

                 GLuint posLoc = glGetUniformLocation(item->shaderProgram, posName.c_str());
                 GLuint colorLoc = glGetUniformLocation(item->shaderProgram, colorName.c_str());
                 GLuint intensityLoc = glGetUniformLocation(item->shaderProgram, intensityName.c_str());

                 if (i < pointLights.size())
                 {
                     glUniform3f(posLoc, pointLights[i].position.x, pointLights[i].position.y, pointLights[i].position.z);
                     glUniform3f(colorLoc, pointLights[i].color.x, pointLights[i].color.y, pointLights[i].color.z);
                     glUniform1f(intensityLoc, pointLights[i].intensity);
                 }
                 else
                 {
                     // û�и�������Դ������ΪĬ��ֵ
                     glUniform3f(posLoc, 0.0f, 0.0f, 0.0f);
                     glUniform3f(colorLoc, 0.0f, 0.0f, 0.0f);
                     glUniform1f(intensityLoc, 0.0f);
                 }
             }

             // ����ƽ�й�����
             // ����ƽ�й�����ɫ���ж�Ӧ uniform ����Ϊ��
             //   parallelLightDirection, parallelLightColor, parallelLightIntensity
             Game::CustomParallelLight parallelLight = lightController->GetParallelLight();
             GLuint parallelDirLoc = glGetUniformLocation(item->shaderProgram, "parallelLightDirection");
             GLuint parallelColorLoc = glGetUniformLocation(item->shaderProgram, "parallelLightColor");
             GLuint parallelIntensityLoc = glGetUniformLocation(item->shaderProgram, "parallelLightIntensity");
             glUniform3f(parallelDirLoc, parallelLight.direction.x, parallelLight.direction.y, parallelLight.direction.z);
             glUniform3f(parallelColorLoc, parallelLight.color.x, parallelLight.color.y, parallelLight.color.z);
             glUniform1f(parallelIntensityLoc, parallelLight.intensity);

             // �����ֵ�Ͳ������
             // ���趨����һ���� MAX_FLASHLIGHTS (���� #define MAX_FLASHLIGHTS 2) ������ɫ���ж��������� uniform ���飺
             //   flashLightPos[], flashLightDirection[], flashLightColor[], flashLightIntensity[], flashLightCutoff[]
             auto flashLights = lightController->GetFlashLights();
             for (int j = 0; j < MAX_LIGHTS; j++)
             {
                 std::string flashPosName = "flashLightPos[" + std::to_string(j) + "]";
                 std::string flashDirName = "flashLightDirection[" + std::to_string(j) + "]";
                 std::string flashColorName = "flashLightColor[" + std::to_string(j) + "]";
                 std::string flashIntensityName = "flashLightIntensity[" + std::to_string(j) + "]";
                 std::string flashCutoffName = "flashLightCutoff[" + std::to_string(j) + "]";

                 GLuint flashPosLoc = glGetUniformLocation(item->shaderProgram, flashPosName.c_str());
                 GLuint flashDirLoc = glGetUniformLocation(item->shaderProgram, flashDirName.c_str());
                 GLuint flashColorLoc = glGetUniformLocation(item->shaderProgram, flashColorName.c_str());
                 GLuint flashIntensityLoc = glGetUniformLocation(item->shaderProgram, flashIntensityName.c_str());
                 GLuint flashCutoffLoc = glGetUniformLocation(item->shaderProgram, flashCutoffName.c_str());

                 if (j < flashLights.size())
                 {
                     glUniform3f(flashPosLoc, flashLights[j].position.x, flashLights[j].position.y, flashLights[j].position.z);
                     glUniform3f(flashDirLoc, flashLights[j].direction.x, flashLights[j].direction.y, flashLights[j].direction.z);
                     glUniform3f(flashColorLoc, flashLights[j].color.x, flashLights[j].color.y, flashLights[j].color.z);
                     glUniform1f(flashIntensityLoc, flashLights[j].intensity);
                     glUniform1f(flashCutoffLoc, flashLights[j].cutoff);
                 }
                 else
                 {
                     glUniform3f(flashPosLoc, 0.0f, 0.0f, 0.0f);
                     glUniform3f(flashDirLoc, 0.0f, 0.0f, 0.0f);
                     glUniform3f(flashColorLoc, 0.0f, 0.0f, 0.0f);
                     glUniform1f(flashIntensityLoc, 0.0f);
                     glUniform1f(flashCutoffLoc, 0.0f);
                 }
             }

             }

             //--����ԴӰ�� �򵥴���
             glUseProgram(item->shaderProgram);

             // ��ȡÿ������Ĺ�Դ����λ��
             GLuint lightPosLoc = glGetUniformLocation(item->shaderProgram, "lightPos");
             GLuint lightColorLoc = glGetUniformLocation(item->shaderProgram, "lightColor");
             GLuint lightIntensityLoc = glGetUniformLocation(item->shaderProgram, "lightIntensity");
             GLuint viewPos = glGetUniformLocation(item->shaderProgram, "viewPos");
             glm::vec3 viewP = glm::vec3(controller->front);

             // ���ù�Դ����
             glUniform3f(lightPosLoc, pointLight.position.x, pointLight.position.y, pointLight.position.z);
             glUniform3f(lightColorLoc, pointLight.color.x, pointLight.color.y, pointLight.color.z);
             glUniform3f(viewPos, viewP.x, viewP.y, viewP.z);
             glUniform1f(lightIntensityLoc, pointLight.intensity);



#endif // !OBSOLETE_CODE_KAKA
