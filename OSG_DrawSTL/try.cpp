/*#include <iostream>
#include <osg/Group>
#include <osg/PositionAttitudeTransform>
#include <osg/Vec3>
#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>

int uniqueLightNumber = 0;

osg::Light *createLight(Vec4 color)
{  
osg::Light *light = new osg::Light();
// each light must have a unique number
light->setLightNum(uniqueLightNumber++);
// we set the light's position via a PositionAttitudeTransform object
light->setPosition(osg::Vec4(0.0, 0.0, 0.0, 1.0));
light->setDiffuse(color);
light->setSpecular(osg::Vec4(1.0, 1.0, 1.0, 1.0));
light->setAmbient(osg::Vec4(0.0, 0.0, 0.0, 1.0));
 
return light;
}

int main()
{
    
   // Create a viewer, use it to view the model
   osgViewer::Viewer viewer;
   osg::Group* root = new osg::Group();
   osg::Geode* pyramidGeode = new osg::Geode();
   osg::Geometry* pyramidGeometry = new osg::Geometry();
   
   pyramidGeode->addDrawable(pyramidGeometry); 
   root->addChild(pyramidGeode);
   osg::Vec3Array* pyramidVertices = new osg::Vec3Array;
   pyramidVertices->push_back( osg::Vec3( 0, 0, 0) ); // front left
   pyramidVertices->push_back( osg::Vec3(10, 0, 0) ); // front right
   pyramidVertices->push_back( osg::Vec3(10,10, 0) ); // back right 
   pyramidVertices->push_back( osg::Vec3( 0,10, 0) ); // back left 
   pyramidVertices->push_back( osg::Vec3( 5, 5,10) ); // peak
   pyramidGeometry->setVertexArray( pyramidVertices );
   osg::DrawElementsUInt* pyramidBase = 
   new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
   pyramidBase->push_back(3);
   pyramidBase->push_back(2);
   pyramidBase->push_back(1);
   pyramidBase->push_back(0);
   pyramidGeometry->addPrimitiveSet(pyramidBase);
   
   osg::DrawElementsUInt* pyramidFaceOne = 
   new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
   pyramidFaceOne->push_back(0);
   pyramidFaceOne->push_back(1);
   pyramidFaceOne->push_back(4);
   pyramidGeometry->addPrimitiveSet(pyramidFaceOne);

   osg::DrawElementsUInt* pyramidFaceTwo = 
   new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
   pyramidFaceTwo->push_back(1);
   pyramidFaceTwo->push_back(2);
   pyramidFaceTwo->push_back(4);
   pyramidGeometry->addPrimitiveSet(pyramidFaceTwo);

   osg::DrawElementsUInt* pyramidFaceThree = 
   new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
   pyramidFaceThree->push_back(2);
   pyramidFaceThree->push_back(3);
   pyramidFaceThree->push_back(4);
   pyramidGeometry->addPrimitiveSet(pyramidFaceThree);

   osg::DrawElementsUInt* pyramidFaceFour = 
   new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
   pyramidFaceFour->push_back(3);
   pyramidFaceFour->push_back(0);
   pyramidFaceFour->push_back(4);
   pyramidGeometry->addPrimitiveSet(pyramidFaceFour);
 
   // Declare and initialize a transform node.
   osg::PositionAttitudeTransform* pyramidTwoXForm = new osg::PositionAttitudeTransform();

   

// Use the 'addChild' method of the osg::Group class to
// add the transform as a child of the root node and the
// pyramid node as a child of the transform.
   root->addChild(pyramidTwoXForm);
   pyramidTwoXForm->addChild(pyramidGeode);
   
    //LIGHT CODE ------------------------
    osg::ref_ptr<osg::Group> lightGroup (new osg::Group);
    osg::ref_ptr<osg::StateSet> lightSS (root->getOrCreateStateSet());
    osg::ref_ptr<osg::LightSource> lightSource1 = new osg::LightSource;
    osg::ref_ptr<osg::LightSource> lightSource2 = new osg::LightSource;

    // create a local light.

    //Light markers: small spheres
    osg::Geode *lightMarkerGeode = new osg::Geode();
    lightMarkerGeode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3() , 1.0)));
    //osg::ref_ptr<osg::Geode> lightMarkerGeode (new osg::Geode);
    //lightMarkerGeode->addDrawable(new osg::Drawable(new osg::Sphere))
    //lightMarkerGeode->addDrawable(new osg::Drawable(new osg::Sphere(osg::Vec3f(xCenter,yCenter,75),10.0f)));

    //Tuto 9: lighting code
    root->addChild(lightGroup.get());
    //Tuto 9: Adding the light marker geode
    root->addChild(lightMarkerGeode);

// Declare and initialize a Vec3 instance to change the
// position of the tank model in the scene
   osg::Vec3 pyramidTwoPosition(15,0,0);
   pyramidTwoXForm->setPosition( pyramidTwoPosition ); 
   
   
   // Enter rendering loop
   viewer.setSceneData( root );

   viewer.realize();

   viewer.run();
}
*/