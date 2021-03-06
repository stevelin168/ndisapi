#pragma once

namespace winsys {

	// --------------------------------------------------------------------------------
	/// <summary>
	/// simple wrapper class for Windows handle
	/// </summary>
	// --------------------------------------------------------------------------------
	class safe_object_handle : public std::unique_ptr<std::remove_pointer<HANDLE>::type, void(*)(HANDLE)>
	{
	public:
		// ********************************************************************************
		/// <summary>
		/// constructs the object from the existing handle value
		/// </summary>
		/// <param name="handle"></param>
		// ********************************************************************************
		explicit safe_object_handle(HANDLE handle) : unique_ptr(handle, &safe_object_handle::close)
		{
		}

		// ********************************************************************************
		/// <summary>
		/// destructor declared virtual for the convenience
		/// </summary>
		// ********************************************************************************
		virtual ~safe_object_handle() {}

		// ********************************************************************************
		/// <summary>
		/// returns the stored handle value
		/// </summary>
		// ********************************************************************************
		explicit operator HANDLE() const
		{
			return get();
		}

		// ********************************************************************************
		/// <summary>
		/// checks the stored handle value for validity
		/// </summary>
		/// <returns>true if valid, false otherwise</returns>
		// ********************************************************************************
		bool valid() const
		{
			return ((get() != INVALID_HANDLE_VALUE) && (get() != nullptr));
		}

	private:
		// ********************************************************************************
		/// <summary>
		/// deleter for the stored windows handle (calls CloseHandle for the handle)
		/// </summary>
		/// <param name="handle">windows handle to close</param>
		// ********************************************************************************
		static void close(HANDLE handle)
		{
			if ((handle != INVALID_HANDLE_VALUE) && (handle != nullptr))
				::CloseHandle(handle);
		}
	};
}
