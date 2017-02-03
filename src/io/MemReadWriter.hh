
#include "Reader.hh"

namespace Sirikata {
	
	class SIRIKATA_EXPORT MemReadWriter : public Sirikata::DecoderWriter, public Sirikata::DecoderReader {
	
	    std::vector<Sirikata::uint8, JpegAllocator<uint8_t>> mBuffer;
	    std::size_t mReadCursor;
	    std::size_t mWriteCursor;
	
		public:
		    MemReadWriter(JpegAllocator<uint8_t> const& alloc) : mBuffer(alloc) {
		        mReadCursor = 0;
		        mWriteCursor = 0;
		    }
		
		    void Close() {
		        mReadCursor = 0;
		        mWriteCursor = 0;
		    }
	    
			void SwapIn(std::vector<Sirikata::uint8, JpegAllocator<uint8_t>>& buffer, size_t offset) {
		        mReadCursor = offset;
		        mWriteCursor = buffer.size();
		        buffer.swap(mBuffer);
		    }
	    
			void CopyIn(std::vector<Sirikata::uint8, JpegAllocator<uint8_t>> const& buffer, size_t offset) {
		        mReadCursor = offset;
		        mWriteCursor = buffer.size();
		        mBuffer = buffer;
		    }
	    
			virtual std::pair<Sirikata::uint32, Sirikata::JpegError> Write(const Sirikata::uint8* data, unsigned int size);
		    virtual std::pair<Sirikata::uint32, Sirikata::JpegError> Read(Sirikata::uint8* data, unsigned int size);
	    
			std::vector<Sirikata::uint8, JpegAllocator<uint8_t>> &buffer() {
		        return mBuffer;
		    }
	    
			std::vector<Sirikata::uint8, JpegAllocator<uint8_t>> const& buffer() const {
		        return mBuffer;
		    }
	};

}
