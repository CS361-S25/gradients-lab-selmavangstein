#include "emp/web/Animate.hpp"
#include "emp/web/web.hpp"

emp::web::Document doc{"target"};

class GradientAnimator : public emp::web::Animate {

    const int num_x_boxes = 10;
    const int num_y_boxes = 10;
    const int cell_size = 25;
    const double width = num_x_boxes * cell_size;
    const double height = num_y_boxes * cell_size;
    double update = 0;

    std::vector<std::vector<float>> cells;
    emp::web::Canvas canvas{width, height, "canvas"};

    public:

        GradientAnimator() {
            doc << canvas;
            doc << GetToggleButton("Toggle");
            doc << GetStepButton("Step");
            cells.resize(num_x_boxes, std::vector<float>(num_y_boxes, 1));
            cells[5][5] = 0;
            cells[2][3] = 0.6;
            cells[1][7] = 0.2;
        }

        void DoFrame() override{
            canvas.Clear();
            update++;

            //copy cell structure to keep track of the current state
            std::vector<std::vector<float>> new_cells = cells;

            //canvas.Text(*new emp::Point(10,10), std::to_string(update));
            //canvas.Rect(10, 10, 10, 10, emp::ColorHSV(0, 0.5, 0.5), "black");

            //loop over all cells and set color to be (x/num_x_boxes, y/num_y_boxes, 0.5) using emp::ColorHSV to create a cool gradient
            /* for (int x = 0; x < num_x_boxes; x++) {
                for (int y = 0; y < num_y_boxes; y++) {
                    float r = (float)x / num_x_boxes;
                    float g = (float)y / num_y_boxes;
                    float b = 0.5;
                    canvas.Rect(x * cell_size, y * cell_size, cell_size, cell_size, emp::ColorHSV(r, g, b), "black");
                }
            } */

            //Define update rules - each cell should take the value of its leftmost neighbor, with wrap around
            for (int x = 0; x < num_x_boxes; x++) {
                for (int y = 0; y < num_y_boxes; y++) {
                    if (x == 0) {
                        new_cells[x][y] = cells[num_x_boxes - 1][y];
                    } else {
                        new_cells[x][y] = cells[x - 1][y];
                    }
                }
            }
            //update cells to be the new cells
            cells = new_cells;

            //draw the cells
            for (int x = 0; x < num_x_boxes; x++) {
                for (int y = 0; y < num_y_boxes; y++) {
                    float b = cells[x][y];
                    canvas.Rect(x * cell_size, y * cell_size, cell_size, cell_size, emp::ColorHSV(0, 0, b), "black");
                }
            }
        }
};

GradientAnimator gradient_animator;

int main(){
    gradient_animator.Step();
}