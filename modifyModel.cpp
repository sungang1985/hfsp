#include <osg/Node>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osg/Texture2D>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Image>
#include <osg/NodeVisitor>

class ModifyVisitor : public osg::NodeVisitor {
public:
    ModifyVisitor(float scaleFactor)
        : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN),
          scaleFactor_(scaleFactor) {}

    virtual void apply(osg::Geode& geode) {
        for (unsigned int i = 0; i < geode.getNumDrawables(); ++i) {
            osg::Geometry* geometry = geode.getDrawable(i)->asGeometry();

            if (geometry) {
                // Modify the height of vertices
                osg::Vec3Array* vertices = dynamic_cast<osg::Vec3Array*>(geometry->getVertexArray());
                if (vertices) {
                    for (osg::Vec3& vertex : *vertices) {
                        vertex.z() *= scaleFactor_;
                    }
                    vertices->dirty();
                }

                // Adjust texture coordinates
                osg::Vec2Array* texCoords = dynamic_cast<osg::Vec2Array*>(geometry->getTexCoordArray(0));
                if (texCoords) {
                    for (osg::Vec2& texCoord : *texCoords) {
                        texCoord.y() *= scaleFactor_;
                    }
                    texCoords->dirty();
                }
            }
        }

        traverse(geode);
    }

private:
    float scaleFactor_;
};

int main(int argc, char** argv) {
    if (argc < 4) {
        std::cout << "Usage: " << argv[0] << " <input.osgb> <scale_factor> <output.osgb>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    float scaleFactor = std::stof(argv[2]);
    std::string outputFile = argv[3];

    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile(inputFile);

    if (!model) {
        std::cerr << "Error: Unable to load input model." << std::endl;
        return 1;
    }

    ModifyVisitor modifyVisitor(scaleFactor);
    model->accept(modifyVisitor);

    if (!osgDB::writeNodeFile(*model, outputFile)) {
        std::cerr << "Error: Unable to save modified model." << std::endl;
        return 1;
    }

    return 0;
}
