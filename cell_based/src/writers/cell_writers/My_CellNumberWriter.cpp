

#include "My_CellNumberWriter.hpp"
#include "AbstractCellPopulation.hpp"

template<unsigned ELEMENT_DIM, unsigned SPACE_DIM>
My_CellNumberWriter<ELEMENT_DIM, SPACE_DIM>::My_CellNumberWriter()
    : AbstractCellWriter<ELEMENT_DIM, SPACE_DIM>("cellnumber.dat")
{
    this->mVtkCellDataName = "Cell Number";
}

template<unsigned ELEMENT_DIM, unsigned SPACE_DIM>
double My_CellNumberWriter<ELEMENT_DIM, SPACE_DIM>::(CellPtr pCell, AbstractCellPopulation<ELEMENT_DIM, SPACE_DIM>* pCellPopulation)
{
    
}




template<unsigned ELEMENT_DIM, unsigned SPACE_DIM>
double CellRadiusWriter<ELEMENT_DIM, SPACE_DIM>::GetCellDataForVtkOutput(CellPtr pCell, AbstractCellPopulation<ELEMENT_DIM, SPACE_DIM>* pCellPopulation)
{
    double cell_radius = 0.0;
    if (dynamic_cast<NodeBasedCellPopulation<SPACE_DIM>*>(pCellPopulation))
    {
        unsigned node_index = pCellPopulation->GetLocationIndexUsingCell(pCell);
        cell_radius = pCellPopulation->GetNode(node_index)->GetRadius();
    }
    return cell_radius;
}

template<unsigned ELEMENT_DIM, unsigned SPACE_DIM>
double CellIdWriter<ELEMENT_DIM, SPACE_DIM>::GetCellDataForVtkOutput(CellPtr pCell, AbstractCellPopulation<ELEMENT_DIM, SPACE_DIM>* pCellPopulation)
{
    double cell_id = pCell->GetCellId();
    return cell_id;
}
