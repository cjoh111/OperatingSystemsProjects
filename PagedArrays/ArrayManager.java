import java.util.ArrayList;

public class ArrayManager {
	private int numFrames;
	private int frameSize;
	private int[] data;
	private ArrayList freeFrameList;

	public ArrayManager(int numFrames, int frameSize) {
		this.numFrames = numFrames;
		this.frameSize = frameSize;
		data = new int[numFrames * frameSize];
		freeFrameList = new ArrayList<Integer>();
		for(int i = 0; i < numFrames; i++){
			freeFrameList.add(i);
		}
	}

	public Array createArray(int size) throws OutOfMemoryException {
		int framesNeeded = 0;
		if(size % frameSize == 0) {
			framesNeeded = size / frameSize;
		} else {
			framesNeeded = size / frameSize + 1;
		}

		if (freeFrameList.size() < framesNeeded) {
			String exceptionMessage = String.format("Cannot create array of size %d with %d frames of %d integers", size, freeFrameList.size(), frameSize);
			throw new OutOfMemoryException(exceptionMessage);
		} else {
			int[] pageTable = new int[framesNeeded];
			for(int i = 0; i< framesNeeded; i++){
				pageTable[i] = (int) freeFrameList.remove(0);
			}
			return new PagedArray(pageTable, size);
		}
	}

	public Array aliasArray(Array a) {
		PagedArray pa = (PagedArray) a;
		return pa;
	}

	public void deleteArray(Array a) {
		PagedArray pa = (PagedArray) a;
		int[] PAPageTable = pa.getPageTable();
		for( int i = 0; i < pa.getPageTable().length; i++){
			freeFrameList.add(PAPageTable[i]);
		}
		pa.setLength(0);
	}

	public void resizeArray(Array a, int newSize) throws OutOfMemoryException {
		int newFramesNeeded, framesUsed = 0;
		PagedArray pa = (PagedArray) a;
		framesUsed = pa.getPageTable().length;

		if(newSize % frameSize == 0){
			newFramesNeeded = newSize / frameSize;
		} else {
			newFramesNeeded = newSize / frameSize + 1;
		}
		if(newFramesNeeded > framesUsed){ //new size is greater than original
			if(freeFrameList.size() < newFramesNeeded - framesUsed) {
				throw new OutOfMemoryException("Cannot resize array -- not enough frames");
			} else {
				int[] pageTable = new int[newFramesNeeded];
				int[] oldPageTable = pa.getPageTable();
				for(int i = 0; i < oldPageTable.length; i++) { //copy pages from previous page table
					pageTable[i] = oldPageTable[i];
				}
				for(int k = oldPageTable.length; k < newFramesNeeded; k++){ //assign new pages to new page table as needed from freeFrameList
					if(pageTable[k] == 0) {
						pageTable[k] = (int) freeFrameList.remove(0);
					}
				}
				pa.setLength(newSize);
				pa.setPageTable(pageTable);
			}
		} else if (newFramesNeeded == framesUsed) { //new size is smaller than original
			pa.setLength(newSize);
		} else {
			int[] pageTable = new int[newFramesNeeded];
			int[] oldPageTable = pa.getPageTable();
			for(int i = 0; i <pageTable.length; i++) {
				pageTable[i] = oldPageTable[i];
			}
			for(int k = pageTable.length; k < oldPageTable.length; k++){
				freeFrameList.add(oldPageTable[k]);
			}
			pa.setLength(newSize);
			pa.setPageTable(pageTable);
		}


	}

	public void printMemory() {
		double percentageUsed = 0.0;
		double freeFrameListSize = freeFrameList.size();
		percentageUsed = 100 * ((double)numFrames - freeFrameListSize) / (double) numFrames;
		System.out.printf("Memory [%dx%d] %.2f%% full\n", numFrames, frameSize, percentageUsed);
		for( int i = 0; i < numFrames; i++){
			if(freeFrameList.contains(i)) {
				System.out.printf("-");
			} else {
				System.out.printf("X");
			}
		}
		System.out.println();
	}

	private class PagedArray implements Array {
		// Your instance variables here
		public int[] pT;
		public int size;

		public PagedArray(int[] pageTable, int size) {
			this.size = size;
			pT = pageTable;
		}

		public int getValue(int index) throws SegmentationViolationException {
			if(index >= size | index < 0){
				String exceptionMessage = String.format("Index %d is out of range. Expected 0->%d", index, size-1);
				throw new SegmentationViolationException(exceptionMessage);
			} else {
				int page = index / frameSize;
				int offset = index % frameSize;
				int frame = pT[page];
				int value = frame * page * offset;
				return data[value];
			}
		}

		public void setValue(int index, int val) throws SegmentationViolationException {
			if(index >= size | index < 0) {
				String exceptionMessage = String.format("Index %d is out of range. Expected 0->%d", index, size-1);
				throw new SegmentationViolationException(exceptionMessage);
			} else {
				int page = index / frameSize;
				int offset = index % frameSize;
				int frame = pT[page];
				int value = frame * page * offset;
				data[value] = val;
			}
		}

		public String toString() {
			StringBuilder returnedString = new StringBuilder();
			returnedString.append(String.format("length %d @", size));
			for(int i = 0; i < pT.length; i++){
				returnedString.append(String.format("%d ", pT[i]));
			}
			return returnedString.toString();
		}

		public int[] getPageTable() {
			return pT;
		}

		public void setPageTable(int[] pageTable) {
			pT = pageTable;
		}

		public int length() {
			return size;
		}

		public void setLength(int length) {
			size = length;
		}
	}
}
