/*
Copyright (C) 2001-2020 by Serge Lamikhov-Center

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <elfio/elfio.hpp>
#include <cstring>

using namespace ELFIO;

#include "elfio_c_interop.h"

//-----------------------------------------------------------------------------
// elfio
//-----------------------------------------------------------------------------
pelfio_t elfio_new() { return new elfio; }

void elfio_delete( pelfio_t pelfio ) { delete (elfio*)pelfio; }

void elfio_create( pelfio_t      pelfio,
                   unsigned char file_class,
                   unsigned char encoding )
{
    pelfio->create( file_class, encoding );
}

bool elfio_load( pelfio_t pelfio, const char* file_name )
{
    return pelfio->load( file_name );
}

bool elfio_save( pelfio_t pelfio, const char* file_name )
{
    return pelfio->save( file_name );
}

ELFIO_C_HEADER_ACCESS_GET_IMPL( unsigned char, class );
ELFIO_C_HEADER_ACCESS_GET_IMPL( unsigned char, elf_version );
ELFIO_C_HEADER_ACCESS_GET_IMPL( unsigned char, encoding );
ELFIO_C_HEADER_ACCESS_GET_IMPL( Elf_Word, version );
ELFIO_C_HEADER_ACCESS_GET_IMPL( Elf_Half, header_size );
ELFIO_C_HEADER_ACCESS_GET_IMPL( Elf_Half, section_entry_size );
ELFIO_C_HEADER_ACCESS_GET_IMPL( Elf_Half, segment_entry_size );

ELFIO_C_HEADER_ACCESS_GET_SET_IMPL( unsigned char, os_abi );
ELFIO_C_HEADER_ACCESS_GET_SET_IMPL( unsigned char, abi_version );
ELFIO_C_HEADER_ACCESS_GET_SET_IMPL( Elf_Half, type );
ELFIO_C_HEADER_ACCESS_GET_SET_IMPL( Elf_Half, machine );
ELFIO_C_HEADER_ACCESS_GET_SET_IMPL( Elf_Word, flags );
ELFIO_C_HEADER_ACCESS_GET_SET_IMPL( Elf64_Addr, entry );
ELFIO_C_HEADER_ACCESS_GET_SET_IMPL( Elf64_Off, sections_offset );
ELFIO_C_HEADER_ACCESS_GET_SET_IMPL( Elf64_Off, segments_offset );
ELFIO_C_HEADER_ACCESS_GET_SET_IMPL( Elf_Half, section_name_str_index );

Elf_Half elfio_get_sections_num( pelfio_t pelfio )
{
    return pelfio->sections.size();
}

psection_t elfio_get_section_by_index( pelfio_t pelfio, int index )
{
    return pelfio->sections[index];
}

psection_t elfio_get_section_by_name( pelfio_t pelfio, char* name )
{
    return pelfio->sections[name];
}

psection_t elfio_add_section( pelfio_t pelfio, char* name )
{
    return pelfio->sections.add( name );
}

Elf_Half elfio_get_segments_num( pelfio_t pelfio )
{
    return pelfio->segments.size();
}

psegment_t elfio_get_segment_by_index( pelfio_t pelfio, int index )
{
    return pelfio->segments[index];
}

psegment_t elfio_add_segment( pelfio_t pelfio )
{
    return pelfio->segments.add();
}

//-----------------------------------------------------------------------------
// section
//-----------------------------------------------------------------------------
ELFIO_C_GET_ACCESS_IMPL( section, Elf_Half, index );
ELFIO_C_GET_SET_ACCESS_IMPL( section, Elf_Word, type );
ELFIO_C_GET_SET_ACCESS_IMPL( section, Elf_Xword, flags );
ELFIO_C_GET_SET_ACCESS_IMPL( section, Elf_Word, info );
ELFIO_C_GET_SET_ACCESS_IMPL( section, Elf_Word, link );
ELFIO_C_GET_SET_ACCESS_IMPL( section, Elf_Xword, addr_align );
ELFIO_C_GET_SET_ACCESS_IMPL( section, Elf_Xword, entry_size );
ELFIO_C_GET_SET_ACCESS_IMPL( section, Elf64_Addr, address );
ELFIO_C_GET_SET_ACCESS_IMPL( section, Elf_Xword, size );
ELFIO_C_GET_SET_ACCESS_IMPL( section, Elf_Word, name_string_offset );
ELFIO_C_GET_ACCESS_IMPL( section, Elf64_Off, offset );

void elfio_section_get_name( psection_t psection, char* buffer, int len )
{
    strncpy( buffer, psection->get_name().c_str(), len - 1 );
}

void elfio_section_set_name( psection_t psection, char* buffer )
{
    psection->set_name( buffer );
}

char* elfio_section_get_data( psection_t psection )
{
    return (char*)psection->get_data();
}

void elfio_section_set_data( psection_t  psection,
                             const char* pData,
                             Elf_Word    size )
{
    psection->set_data( pData, size );
}

void elfio_section_append_data( psection_t  psection,
                                const char* pData,
                                Elf_Word    size )
{
    psection->append_data( pData, size );
}

//-----------------------------------------------------------------------------
// segment
//-----------------------------------------------------------------------------
ELFIO_C_GET_ACCESS_IMPL( segment, Elf_Half, index );
ELFIO_C_GET_SET_ACCESS_IMPL( segment, Elf_Word, type );
ELFIO_C_GET_SET_ACCESS_IMPL( segment, Elf_Word, flags );
ELFIO_C_GET_SET_ACCESS_IMPL( segment, Elf_Xword, align );
ELFIO_C_GET_SET_ACCESS_IMPL( segment, Elf_Xword, memory_size );
ELFIO_C_GET_SET_ACCESS_IMPL( segment, Elf64_Addr, virtual_address );
ELFIO_C_GET_SET_ACCESS_IMPL( segment, Elf64_Addr, physical_address );
ELFIO_C_GET_SET_ACCESS_IMPL( segment, Elf_Xword, file_size );
ELFIO_C_GET_ACCESS_IMPL( segment, Elf64_Off, offset );

char* elfio_segment_get_data( psegment_t psegment )
{
    return (char*)psegment->get_data();
}

Elf_Half elfio_segment_add_section_index( psegment_t psegment,
                                          Elf_Half   index,
                                          Elf_Xword  addr_align )
{
    return psegment->add_section_index( index, addr_align );
}

Elf_Half elfio_segment_get_sections_num( psegment_t psegment )
{
    return psegment->get_sections_num();
}

Elf_Half elfio_segment_get_section_index_at( psegment_t psegment, Elf_Half num )
{
    return psegment->get_section_index_at( num );
}

bool elfio_segment_is_offset_initialized( psegment_t psegment )
{
    return psegment->is_offset_initialized();
}

//-----------------------------------------------------------------------------
// symbol
//-----------------------------------------------------------------------------
psymbol_t elfio_symbol_section_accessor_new( pelfio_t   pelfio,
                                             psection_t psection )
{
    return new symbol_section_accessor( *pelfio, psection );
}

void elfio_symbol_section_accessor_delete( psymbol_t psymbol )
{
    delete psymbol;
}

Elf_Xword elfio_symbol_get_symbols_num( psymbol_t psymbol )
{
    return psymbol->get_symbols_num();
}

bool get_symbol( psymbol_t      psymbol,
                 Elf_Xword      index,
                 char*          name,
                 int            name_len,
                 Elf64_Addr*    value,
                 Elf_Xword*     size,
                 unsigned char* bind,
                 unsigned char* type,
                 Elf_Half*      section_index,
                 unsigned char* other )
{
    std::string name_param;
    bool ret = psymbol->get_symbol( index, name_param, *value, *size, *bind,
                                    *type, *section_index, *other );
    strncpy( name, name_param.c_str(), name_len - 1 );

    return ret;
}

Elf_Word elfio_symbol_add_symbol( psymbol_t     psymbol,
                                  Elf_Word      name,
                                  Elf64_Addr    value,
                                  Elf_Xword     size,
                                  unsigned char info,
                                  unsigned char other,
                                  Elf_Half      shndx )
{
    return psymbol->add_symbol( name, value, size, info, other, shndx );
}

Elf_Xword elfio_symbol_arrange_local_symbols(
    psymbol_t psymbol, void ( *func )( Elf_Xword first, Elf_Xword second ) )
{
    return psymbol->arrange_local_symbols( func );
}