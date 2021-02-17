#include <cxxtest/TestSuite.h>
#include "CellBasedSimulationArchiver.hpp"
#include "SmartPointers.hpp"
#include "AbstractCellBasedTestSuite.hpp"
#include "AdhesionPottsUpdateRule.hpp"
#include "CellsGenerator.hpp"
#include "CylindricalHoneycombMeshGenerator.hpp"
#include "ToroidalHoneycombVertexMeshGenerator.hpp"
#include "GeneralisedLinearSpringForce.hpp"
#include "HoneycombMeshGenerator.hpp"
#include "HoneycombVertexMeshGenerator.hpp"
#include "MeshBasedCellPopulationWithGhostNodes.hpp"
#include "NagaiHondaForce.hpp"
#include "SimpleTargetAreaModifier.hpp"
#include "NodeBasedCellPopulation.hpp"
#include "OffLatticeSimulation.hpp"
#include "OnLatticeSimulation.hpp"
#include "PlaneBoundaryCondition.hpp"
#include "PottsBasedCellPopulation.hpp"
#include "PottsMeshGenerator.hpp"
#include "RandomCellKiller.hpp"
#include "RepulsionForce.hpp"
#include "UniformG1GenerationalCellCycleModel.hpp"
#include "SurfaceAreaConstraintPottsUpdateRule.hpp"
#include "TysonNovakCellCycleModel.hpp"
#include "VertexBasedCellPopulation.hpp"
#include "VolumeConstraintPottsUpdateRule.hpp"
#include "VoronoiDataWriter.hpp"

#include "FakePetscSetup.hpp"


class SimulationVT_1 : public AbstractCellBasedTestSuite
{
public:

    /* We next show how to modify the previous test to include 'ghost nodes', which do not
     * correspond to cells but are sometimes needed when using a Voronoi tessellation. We
     * will discuss ghost nodes in more detail in subsequent cell-based tutorials.
     */
    void TestMeshBasedMonolayerWithGhostNodes()
    {
        /* This time we just create a {{{MutableMesh}}} and use that to specify the spatial locations of cells.
         * Here we pass an extra argument to the {{{HoneycombMeshGenerator}}} which adds another 2 rows of
         * nodes round the mesh, known as ghost nodes.*/
        CylindricalHoneycombMeshGenerator generator(6, 8, 2);
        Cylindrical2dMesh* p_mesh = generator.GetCylindricalMesh();

        /* We only want to create cells for non ghost nodes. To find these we get them from the {{{HoneycombMeshGenerator}}}
         * using the method {{{GetCellLocationIndices}}}. We also use a different {{{CellCycleModel}}}. Here we use a
         * {{{TysonNovakCellCycleModel}}} which solves a coupled set of ODEs for each cell to calculate when each cell divides. */
        std::vector<unsigned> location_indices = generator.GetCellLocationIndices();//**Changed**//
        std::vector<CellPtr> cells;
        MAKE_PTR(TransitCellProliferativeType, p_transit_type);
        CellsGenerator<UniformG1GenerationalCellCycleModel, 2> cells_generator; //**Changed**//
        cells_generator.GenerateBasicRandom(cells, location_indices.size(), p_transit_type); //**Changed**//

        /* This time we create a {{{MeshBasedCellPopulation}}} as we are using a {{{MutableMesh}}} and have ghost nodes.
         * We also need to pass the indices of non ghost nodes as an extra argument.*/
        MeshBasedCellPopulationWithGhostNodes<2> cell_population(*p_mesh, cells, location_indices); //**Changed**//

        /* Again Paraview output is explicitly requested.*/
        cell_population.AddPopulationWriter<VoronoiDataWriter>();

        /* We create an {{{OffLatticeSimulation}}} object as before, all we change is the output directory and the end time.
         * The Tyson Novak model is for yeast cells and therefore cells proliferate much more often and so we run the simulation for
         * less time to keep cell numbers relatively small for this demo.
         */
        OffLatticeSimulation<2> simulator(cell_population);
        simulator.SetOutputDirectory("CellBased_VT"); //**Changed**//
        simulator.SetSamplingTimestepMultiple(12);
        simulator.SetEndTime(20.0); //**Changed**//

        /* We use the same {{{Force}}} as before and run the simulation in the same way.*/
        MAKE_PTR(GeneralisedLinearSpringForce<2>, p_force);
        simulator.AddForce(p_force);

        /* We now want to impose the condition y>0 on the cells. To do this we create a "shared pointer" to a {{{PlaneBoundaryCondition}}}.
         * Much like the {{{RandomCellKiller}}} earlier we pass arguments to the constructor (a point (0,0) on the plane (line in 2D) and an outward pointing normal to the plane (0,-1) ) using the {{{MAKE_PTR_ARGS}}} macro.*/
        c_vector<double,2> point = zero_vector<double>(2);
        c_vector<double,2> normal = zero_vector<double>(2);
        normal(1) = -1.0;
        MAKE_PTR_ARGS(PlaneBoundaryCondition<2>, p_bc, (&cell_population, point, normal));
        simulator.AddCellPopulationBoundaryCondition(p_bc);

        simulator.Solve();

    }

    /* To visualize the results, open a new terminal, {{{cd}}} to the Chaste directory,
     * then {{{cd}}} to {{{anim}}}. Then do: {{{java Visualize2dCentreCells /tmp/$USER/testoutput/CellBased_VT/results_from_time_0}}}.
     * We may have to do: {{{javac Visualize2dCentreCells.java}}} beforehand to create the
     * java executable.
     */

};
