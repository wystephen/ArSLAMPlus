//
// Created by steve on 17-2-3.
//

/**
 *                             _ooOoo_
 *                            o8888888o
 *                            88" . "88
 *                            (| -_- |)
 *                            O\  =  /O
 *                         ____/`---'\____
 *                       .'  \\|     |//  `.
 *                      /  \\|||  :  |||//  \
 *                     /  _||||| -:- |||||-  \
 *                     |   | \\\  -  /// |   |
 *                     | \_|  ''\---/''  |   |
 *                     \  .-\__  `-`  ___/-. /
 *                   ___`. .'  /--.--\  `. . __
 *                ."" '<  `.___\_<|>_/___.'  >'"".
 *               | | :  `- \`.;`\ _ /`;.`/ - ` : | |
 *               \  \ `-.   \_ __\ /__ _/   .-` /  /
 *          ======`-.____`-.___\_____/___.-`____.-'======
 *                             `=---='
 *          ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *                     佛祖保佑        永无BUG
 *            佛曰:
 *                   写字楼里写字间，写字间里程序员；
 *                   程序人员写程序，又拿程序换酒钱。
 *                   酒醒只在网上坐，酒醉还来网下眠；
 *                   酒醉酒醒日复日，网上网下年复年。
 *                   但愿老死电脑间，不愿鞠躬老板前；
 *                   奔驰宝马贵者趣，公交自行程序员。
 *                   别人笑我忒疯癫，我笑自己命太贱；
 *                   不见满街漂亮妹，哪个归得程序员？
*/

#include <iostream>

#include "g2o/core/sparse_optimizer.h"
#include "g2o/core/block_solver.h"
#include "g2o/core/optimization_algorithm_gauss_newton.h"
#include "g2o/core/optimization_algorithm_levenberg.h"
#include "g2o/solvers/csparse/linear_solver_csparse.h"

#include "g2o/core/factory.h"
//#include "g2o/types/slam3d/types_slam3d.h"
//#include "g2o/types/slam2d/types_slam2d.h"

#include "g2o/stuff/command_args.h"

using namespace std;
using namespace g2o;

// we use the 2D and 3D SLAM types here
G2O_USE_TYPE_GROUP(slam2d);
G2O_USE_TYPE_GROUP(slam3d);

int main(int argc, char** argv)
{
    // Command line parsing
    int maxIterations;
    string outputFilename;
    string inputFilename;
    CommandArgs arg;
    arg.param("i", maxIterations, 10, "perform n iterations, if negative consider the gain");
    arg.param("o", outputFilename, "", "output final version of the graph");
    arg.paramLeftOver("graph-input", inputFilename, "", "graph file which will be processed");
    arg.parseArgs(argc, argv);

    // create the linear solver
    BlockSolverX::LinearSolverType * linearSolver = new LinearSolverCSparse<BlockSolverX::PoseMatrixType>();

    // create the block solver on top of the linear solver
    BlockSolverX* blockSolver = new BlockSolverX(linearSolver);

    // create the algorithm to carry out the optimization
    //OptimizationAlgorithmGaussNewton* optimizationAlgorithm = new OptimizationAlgorithmGaussNewton(blockSolver);
    OptimizationAlgorithmLevenberg* optimizationAlgorithm = new OptimizationAlgorithmLevenberg(blockSolver);

    // NOTE: We skip to fix a variable here, either this is stored in the file
    // itself or Levenberg will handle it.

    // create the optimizer to load the data and carry out the optimization
    SparseOptimizer optimizer;
    optimizer.setVerbose(true);
    optimizer.setAlgorithm(optimizationAlgorithm);

    ifstream ifs(inputFilename.c_str());
    if (! ifs) {
        cerr << "unable to open " << inputFilename << endl;
        return 1;
    }
    optimizer.load(ifs);
    optimizer.initializeOptimization();
    optimizer.optimize(maxIterations);

    if (outputFilename.size() > 0) {
        if (outputFilename == "-") {
            cerr << "saving to stdout";
            optimizer.save(cout);
        } else {
            cerr << "saving " << outputFilename << " ... ";
            optimizer.save(outputFilename.c_str());
        }
        cerr << "done." << endl;
    }
    return 0;
}


