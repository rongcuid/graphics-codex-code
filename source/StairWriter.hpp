#ifndef SOURCE_STAIRWRITER_INCLUDED
#define SOURCE_STAIRWRITER_INCLUDED

#include <fstream>

class StairWriter {
public:
  StairWriter(std::ostream &ostr) : m_ostr(ostr) {}

  void write_line(const std::string &s) { m_ostr << s << std::endl; }

  void write_property(const std::string &name, const std::string &value) {
    m_ostr << name << " = " << value << ";" << std::endl;
  }

  void write_model() {
    write_line("models = {");
    write_line("cubeModel = ArticulatedModel::Specification {\n"
               "filename = \"model/cube/cube.obj\";\n"
               "preprocess = {\n"
               "setMaterial(all(), \"model/crate/woodcrate-B.png\");\n"
               "transformGeometry(all(), Matrix4::scale(1.0, 0.2, 0.4));\n"
               "};\n"
               "};");
    write_line("};");
  }

  void write_stair(int i) {
    float x, y, z, yaw, pitch, row;
    x = 0.;
    y = 0.2 * i;
    z = 0.;
    yaw = 15. * i;
    pitch = 0.0;
    row = 0.0;
    m_ostr << "stair_" << i << " = VisibleEntity {" << std::endl;
    write_line("  model = \"cubeModel\";");
    m_ostr << "  frame = CFrame::fromXYZYPRDegrees(" 
      << x << ", " << y << ", " << z << ", " << yaw << ", " << pitch << ", " << row << ");" << std::endl;
    write_line("};");
  }

  void write_stairs() {
    for (int i=0; i<50; ++i) {
      write_stair(i);
    }
  }

  void write_camera() {
    write_line("camera = Camera {");
    write_line("frame = CFrame::fromXYZYPRDegrees(0, 0, 5);");
    write_line("};");
  }

  void write_entities() {
    write_line("entities = {");
    write_stairs();
    write_camera();
    write_line("};");
  }

  void write() {
    write_line("{");
    write_property("name", "\"Stairs\"");
    write_model();
    write_entities();
    write_line("};");
  }

private:
  std::ostream &m_ostr;
};


#endif /* SOURCE_STAIRWRITER_INCLUDED */
