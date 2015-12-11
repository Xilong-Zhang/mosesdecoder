#pragma once

#include <sys/stat.h> //For finding size of file
#include "vocabid.hh"
#include <algorithm> //toLower
#include "probing_hash_utils.hh"
#include "huffmanish.hh"
#include "hash.hh" //Includes line splitter
#include "../../Vector.h"

#define API_VERSION 3

namespace Moses2
{

char * read_binary_file(char * filename);

class QueryEngine
{
  unsigned char * binary_mmaped; //The binari phrase table file
  std::map<unsigned int, std::string> vocabids;
  std::map<uint64_t, std::string> source_vocabids;

  Table table;
  char *mem; //Memory for the table, necessary so that we can correctly destroy the object

  HuffmanDecoder decoder;

  size_t binary_filesize;
  size_t table_filesize;
  int num_scores;
  bool is_reordering;
public:
  QueryEngine (const char *);
  ~QueryEngine();
  std::pair<bool, std::vector<target_text> > query(const StringPiece &source_phrase);
  std::pair<bool, std::vector<target_text> > query(uint64_t source_phrase[], size_t size);
  void printTargetInfo(const std::vector<target_text> &target_phrases);
  const std::map<unsigned int, std::string> &getVocab() const {
    return decoder.get_target_lookup_map();
  }

  const std::map<uint64_t, std::string> &getSourceVocab() const {
    return source_vocabids;
  }

};

}


