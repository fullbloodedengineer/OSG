#include <osg/ShapeDrawable>
#include <osg/Geometry>
#include <osg/Material>
#include <osg/StateSet>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/PositionAttitudeTransform>
#include <osgViewer/Viewer>
#include <osgGA/TrackballManipulator>
#include <parse_stl.h>
#include <iostream>


using namespace osg;
int uniqueLightNumber = 0;
int const LIGHTS = 3;

PositionAttitudeTransform *meshTransform;
PositionAttitudeTransform *lightTransform[LIGHTS];
StateSet *lightStateSet;

Geode *createMesh(std::vector<stl::triangle> triangles) {
    // vertex array
    Vec3Array *vertexArray = new Vec3Array();
    Vec3Array *normalArray = new Vec3Array();
    DrawElementsUInt *faceArray = new DrawElementsUInt(PrimitiveSet::TRIANGLES, 0);

    //loop over triangles, adding vertex to array
    float maxZ = 0;
    for (stl::triangle t : triangles){
        stl::point normal = t.normal;
        normalArray->push_back(Vec3(normal.x,normal.y,normal.z));
        
        stl::point v1 = t.v1;
        vertexArray->push_back(Vec3(v1.x,v1.y,v1.z));
        faceArray->push_back(vertexArray->size()-1);
        
        if ( v1.z > maxZ ) { maxZ = v1.z; }
        
        stl::point v2 = t.v2;
        vertexArray->push_back(Vec3(v2.x,v2.y,v2.z));
        faceArray->push_back(vertexArray->size()-1);

        stl::point v3 = t.v3;
        vertexArray->push_back(Vec3(v3.x,v3.y,v3.z));
        faceArray->push_back(vertexArray->size()-1);
    }
    
    std::cout << maxZ << std::endl;
    
    Geometry *geometry = new Geometry();
    geometry->setVertexArray(vertexArray);
    //geometry->setNormalArray(normalArray);
    geometry->setNormalBinding(Geometry::BIND_PER_VERTEX);
    geometry->addPrimitiveSet(faceArray);

    Geode *mesh = new Geode();
    mesh->addDrawable(geometry);
    return mesh;
}
 
Light *createLight(Vec4 color)
{  
    Light *light = new Light();
    // each light must have a unique number
    light->setLightNum(uniqueLightNumber++);
    // we set the light's position via a PositionAttitudeTransform object
    light->setPosition(Vec4(0.0, 0.0, 0.0, 1.0));
    light->setDiffuse(color);
    light->setSpecular(Vec4(1.0, 1.0, 1.0, 1.0));
    light->setAmbient( Vec4(0.0, 0.0, 0.0, 1.0));
    light->setConstantAttenuation(1.0f);
    //light->setDirection(osg::Vec3(0.0f, 0.0f, -1.0f));
    return light;
}
 
Material *createSimpleMaterial(Vec4 color)
{
    Material *material = new Material();
    material->setDiffuse(Material::FRONT,  Vec4(0.0, 0.0, 0.0, 1.0));
    material->setEmission(Material::FRONT, color);
    material->setDiffuse(Material::BACK,  Vec4(0.0, 0.0, 0.0, 1.0));
    material->setEmission(Material::BACK, color);

    return material;
}
 
 
Node *startup(auto triangles) {
    // we need the scene's state set to enable the light for the entire scene
    Group *scene = new Group();

    Geode *mesh = createMesh(triangles);
    
    PositionAttitudeTransform *meshTransform = new PositionAttitudeTransform();
    meshTransform->addChild(mesh);
    meshTransform->setPosition(Vec3(0, 0, 0));

    // create a white material
    Material *material = new Material();
    //material->setDiffuse(Material::FRONT,  Vec4(1.0, 1.0, 1.0, 1.0));
    //material->setSpecular(Material::FRONT, Vec4(0.0, 0.0, 0.0, 1.0));
    //material->setAmbient(Material::FRONT,  Vec4(0.1, 0.1, 0.1, 1.0));
    //material->setEmission(Material::FRONT, Vec4(0.0, 0.0, 0.0, 1.0));
    //material->setShininess(Material::FRONT, 25.0);
    material->setDiffuse(Material::BACK,  Vec4(1.0, 1.0, 1.0, 1.0));
    material->setSpecular(Material::BACK, Vec4(0.0, 0.0, 0.0, 1.0));
    material->setAmbient(Material::BACK,  Vec4(0.1, 0.1, 0.1, 1.0));
    material->setEmission(Material::BACK, Vec4(0.0, 0.0, 0.0, 1.0));
    material->setShininess(Material::BACK, 25.0);

    // assign the material to the sphere and cube
    mesh->getOrCreateStateSet()->setAttribute(material);
    
    //---LIGHT CODE----
    lightStateSet = scene->getOrCreateStateSet();

    // Create Lights - Red, Green, Blue
    Vec4 lightColors[] = {Vec4(0.0, 1.0, 0.0, 1.0), Vec4(0.0, 1.0, 0.0, 1.0), Vec4(0.0, 0.0, 1.0, 1.0)};

    Geode *lightMarker[LIGHTS];
    LightSource *lightSource[LIGHTS];

    for (int i = 0; i < LIGHTS; i++) {
        lightMarker[i] = new Geode();
        lightMarker[i]->addDrawable(new ShapeDrawable(new Sphere(Vec3(), 100)));
        lightMarker[i]->getOrCreateStateSet()->setAttribute(createSimpleMaterial(lightColors[i]));

        lightSource[i] = new LightSource();
        lightSource[i]->setLight(createLight(lightColors[i]));
        lightSource[i]->setLocalStateSetModes(StateAttribute::ON);
        lightSource[i]->setStateSetModes(*lightStateSet, StateAttribute::ON);

        lightTransform[i] = new PositionAttitudeTransform();
        lightTransform[i]->addChild(lightSource[i]);
        lightTransform[i]->addChild(lightMarker[i]);
        lightTransform[i]->setPosition(Vec3(0, 0, 5));
        lightTransform[i]->setScale(Vec3(0.1,0.1,0.1));

        scene->addChild(lightTransform[i]);
    }
    
    scene->addChild(meshTransform);
    return scene;
}
 
void update(double time) {
    ///Make the colored lights orbate around the objects
    lightTransform[0]->setPosition(Vec3(std::cos(time), std::sin(time),  0) * 400);
    lightTransform[1]->setPosition(Vec3(0, std::cos(time),  std::sin(time)) * 400);
    lightTransform[2]->setPosition(Vec3(std::sin(time), std::cos(time),  std::sin(time)) * 400);
}
 
int main() {
    std::string stl_file_name = "/home/rankink/NetBeansProjects/CppApplication_2/Darth_Vader_-_Full_Figure_-_LOW.stl";
    auto info = stl::parse_stl(stl_file_name);
    std::vector<stl::triangle> triangles = info.triangles;
    Node *scene = startup(triangles);
 
    osgViewer::Viewer viewer;
    viewer.setSceneData(scene);
    viewer.setCameraManipulator(new osgGA::TrackballManipulator());
    viewer.realize();
    while (!viewer.done()) {
        update(viewer.elapsedTime());
        viewer.frame();
    }
}