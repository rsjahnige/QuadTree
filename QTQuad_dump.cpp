#include <cstddef>
#include <cstring>

#include "Point.h"
#include "BBox.h"
#include "QTQuad.h"

using namespace std;


static const char *dirNames[] = {"Bottom-Left", "Bottom-Right",
			   "Top-Left", "Top-Right"};

void
QTQuad::dump(const BBox &bounds) {
    cout << "[QTQuad bounds=" << bounds;
    if (m_cells == NULL) { // Internal node
	cout << " is INTERNAL:\n";
	for (int q = 0; q < QTQ_NUM_QUADS; q++) {
	    cout << dirNames[q] << " child:" << endl;
	    if (m_quads[q] == NULL) {
		cout << "[NULL]" << endl;
	    } else {
		m_quads[q]->dump(quadBBox(q, bounds));
	    }
	}
    } else {
	cout << " is GRID LEAF:\n";
	for (int y = QTQ_GRID_DIM - 1; y >= 0; --y) {
	    cout << "[";
	    for (int x = 0; x < QTQ_GRID_DIM; x++) {
		char c;

		if (m_cells[x][y] < 0) {
		    c = '-';
		} else if (m_cells[x][y] > 15) {
		    c = '*';
		} else if (m_cells[x][y] > 9) {
		    c = 'a' + m_cells[x][y] - 10;
		} else {
		    c = '0' + m_cells[x][y];
		}
		cout << c;
	    }
	    cout << "]" << endl;
	}
    }
    cout << "]" << endl;
}
