#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
  // step one: Identify all iterators to space charactres
  Corpus corpus;// using Corpus = std::set<Token>;
  auto spaceIterators = find_all(source.begin(), source.end(), ::isspace);// 返回std::vector<Iterator>
  // step two: Generate tokens between consecutive space characters
  auto generateToken = [&source](std::string::iterator it1,std::string::iterator it2){
    return Token{source,it1,it2};
  };//source必须捕获引用，transform需要的是二元函数，只有两个形参
  std::transform(spaceIterators.begin(),spaceIterators.end() -1,spaceIterators.begin()+1,
                std::inserter(corpus, corpus.end()),generateToken);
  //inserter把写入的值插入到corpus的end()位置
  // step three: Get rid of empty tokens
  std::erase_if(corpus,[](const Token& token){
    return token.content.empty();
  });
  return corpus;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  // step one: Skip words that are already correctly spelled
  // 找出拼写有误的单词存入view中
  auto view = std::ranges::views::filter(source, [&dictionary](auto token){return !dictionary.contains(token.content);});
  // step two: Find one-edit-away words in the dictionary using Damerau-Levenshtein
  // 生成Misspelling的set。捕捉dictionary,用view中的每一个token跑该函数
  auto misspellings = std::ranges::views::transform(view,[&dictionary](const Token& token){
    // 对于每一个token，找到所有距离为1的单词组成suggestions
    auto suggestions_lazy = std::ranges::views::filter(dictionary,[&token](std::string str){return (levenshtein(token.content, str) == 1);});
    std::set<std::string> suggestions(suggestions_lazy.begin(), suggestions_lazy.end());// 把views转换为set，不然因为惰性没有实例化
    return Misspelling{token,suggestions};
  });
  // step three: Drop misspellings with no suggestions.
  auto misspellingsWithSuggestions = std::ranges::views::filter(misspellings, [](auto elem){return !elem.suggestions.empty(); });
  auto misspellingsWithSuggestionsSet = std::set<Misspelling>(misspellingsWithSuggestions.begin(), misspellingsWithSuggestions.end());
  return misspellingsWithSuggestionsSet;
};

/* Helper methods */

#include "utils.cpp"