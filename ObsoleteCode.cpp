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






#endif // !OBSOLETE_CODE_KAKA
