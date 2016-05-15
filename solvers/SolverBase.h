//
//  Copyright © 2016 Cody Price. All rights reserved.
//

#ifndef RESEARCHDNNGENERATOR_SOLVERBASE_H
#define RESEARCHDNNGENERATOR_SOLVERBASE_H


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "solver_helpers/Snapshot.h"

enum PoolingType {
    MAX, AVERAGE, STOCHASTIC
};

enum LearningPolicy {
    FIXED, STEP, INV
};

enum SolverMode {
    CPU, GPU
};

class SolverBase {
private:
    std::string mSolverFilename;
    std::string mPrototxtFilename;
    SolverMode mSolverMode;
    int mTestIterations;
    int mTestInterval;
    float mBaseLearningRate;
    float mMomentum;
    float mWeightDecay;
    LearningPolicy mLearningPolicy;
    int mDisplay;
    int mMaxIterations;
    Snapshot *mSnapshot;
    bool mHasSnapshot;

    std::string getLearningPolicy();
    std::string getSolverMode();
    std::string getSnapshotFormat();

public:
    SolverBase(std::string solver_filename, std::string prototxt_filename, SolverMode solver_mode);
    ~SolverBase();
    std::string getSolverFilename();
    void setSolverFilename(std::string solver_filename);
    void setupSolver(int test_iter, int test_inerval, int max_iter, int display, SolverMode solver_mode);
    void setSolverSnapshot(int snapshot, SnapshotFormat snapshot_format, std::string snapshot_prefix);
    void setSolverLearningParams(float base_lr, float momemntum, float weight_decay, LearningPolicy lr_policy);
    void generateSolver();
    std::string toString();
};


#endif //RESEARCHDNNGENERATOR_SOLVERBASE_H
