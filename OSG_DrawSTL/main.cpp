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
#include <osgDB/ReadFile>

using namespace osg;
//int uniqueLightNumber = 0;
//int const LIGHTS = 3;

Geode *createMesh(std::vector<stl::triangle> triangles) {
    // vertex array
    Vec3Array *vertexArray = new Vec3Array();
    Vec3Array *normalArray = new Vec3Array();
    DrawElementsUInt *faceArray = new DrawElementsUInt(PrimitiveSet::TRIANGLES, 0);

    //loop over triangles, adding vertex to array
    float maxX = 0;
    float maxY = 0;
    float maxZ = 0;
    for (stl::triangle t : triangles){
        stl::point normal = t.normal;
        normalArray->push_back(Vec3(normal.x,normal.y,normal.z));
        //normalArray->push_back(Vec3(1.0,0.0,0.0));
        
        stl::point v1 = t.v1;
        vertexArray->push_back(Vec3(v1.x,v1.y,v1.z));
        faceArray->push_back(vertexArray->size()-1);
        
        if ( v1.x > maxX ) { maxX = v1.x; }
        if ( v1.y > maxY ) { maxY = v1.y; }
        if ( v1.z > maxZ ) { maxZ = v1.z; }
        
        stl::point v2 = t.v2;
        vertexArray->push_back(Vec3(v2.x,v2.y,v2.z));
        faceArray->push_back(vertexArray->size()-1);

        stl::point v3 = t.v3;
        vertexArray->push_back(Vec3(v3.x,v3.y,v3.z));
        faceArray->push_back(vertexArray->size()-1);
    }
    
    std::cout << maxX << "," << maxY << "," << maxZ << std::endl;
    
    Geometry *geometry = new Geometry();
    geometry->setVertexArray(vertexArray);
    geometry->setNormalArray(normalArray);
    geometry->setNormalBinding(Geometry::BIND_PER_PRIMITIVE_SET);
    geometry->addPrimitiveSet(faceArray);

    Geode *mesh = new Geode();
    mesh->addDrawable(geometry);
    return mesh;
}
 
Node *startup(auto triangles) {
    // we need the scene's state set to enable the light for the entire scene
    Group *scene = new Group();
    Geode *mesh = createMesh(triangles);
    
    //This loader should work but the plugin seems messed up currently (3rd party lib needed))
    //osg::Node *mesh = osgDB::readNodeFile("./DV.obj");

    PositionAttitudeTransform *meshTransform = new PositionAttitudeTransform();
    meshTransform->addChild(mesh);
    meshTransform->setPosition(Vec3(0, 0, 0));

    // create a white material
    Material *material = new Material();
    material->setDiffuse(Material::Face::FRONT,  Vec4(1.0, 0.5, 0.1, 1.0));
    material->setSpecular(Material::Face::FRONT, Vec4(1.0, 1.0, 1.0, 1.0));
    //material->setAmbient(Material::FRONT,  Vec4(0.1, 0.1, 0.1, 1.0));
    //material->setEmission(Material::FRONT, Vec4(0.0, 0.0, 0.0, .01));
    material->setShininess(Material::Face::FRONT, 63);
    
    // assign the material to the sphere and cube
    mesh->getOrCreateStateSet()->setAttribute(material);
    
    //---LIGHT CODE----
    //lightStateSet = scene->getOrCreateStateSet();
    osg::StateSet* state = scene->getOrCreateStateSet();
    
    //mesh->setStateSet(state);
    
    state->setMode( GL_LIGHTING, osg::StateAttribute::ON );
    //state->setMode( GL_LIGHT0, osg::StateAttribute::ON );
    // Create a white spot light
    osg::ref_ptr<osg::Light> light0 = new osg::Light;
    light0->setLightNum( 0 ); //0-7, default is 0
    light0->setPosition( osg::Vec4( 400, 400, 400, 1.0 ));
    light0->setConstantAttenuation(1.0f);
    
    // create a light source object and add the light to it
    osg::ref_ptr<osg::LightSource> source0 = new osg::LightSource;
    source0->setLight( light0 );
    scene->addChild(source0);
    Geode *lightMarker = new Geode();
    lightMarker->addDrawable(new ShapeDrawable(new Sphere(Vec3(400,400,400), 5)));
    lightMarker->getOrCreateStateSet()->setAttribute(material);
    meshTransform->addChild(lightMarker);
      
    scene->addChild(meshTransform);
    return scene;
}

int main() {
    std::string stl_file_name = "./Darth_Vader_-_Full_Figure_-_LOW.stl";
    auto info = stl::parse_stl(stl_file_name);
    std::vector<stl::triangle> triangles = info.triangles;
    Node *scene = startup(triangles);
 
    osgViewer::Viewer viewer;
    viewer.setSceneData(scene);
    viewer.setCameraManipulator(new osgGA::TrackballManipulator());
    viewer.realize();
    while (!viewer.done()) {
        viewer.frame();
    }
}
