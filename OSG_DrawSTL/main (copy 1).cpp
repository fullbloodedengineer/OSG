// VerySimpleViewer.cpp

#include <iostream>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

int main(int argc, char* argv[])
{
   // Check command-line parameters
   if (argc != 2)
   {
      std::cerr << "Usage: " << argv[0] << " <model file>\n";
      exit(1);
   }

   // Load the model
   osg::ref_ptr<osg::Node> loadedModel = osgDB::readNodeFile(argv[1]);

   if (!loadedModel)
   {
      std::cerr << "Problem opening '" << argv[1] << "'\n";
      exit(1);
   }

   // Create a viewer, use it to view the model
   osgViewer::Viewer viewer;
   viewer.setSceneData(loadedModel);
   
   // Enter rendering loop
   viewer.run();
}