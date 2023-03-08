#ifndef SKIPCONTAINER_H
#define SKIPCONTAINER_H
template<typename ContType>
struct SkipIterator
{

    using ContainerIter=ContType::const_iterator;
    const ContType&  cont;
    ContType::size_type skipindex;
    ContType::size_type currentIndex;
    const ContType::value_type& operator*(){
        return *(cont.begin()+currentIndex);
    }
    SkipIterator operator++(){
        if(++currentIndex == skipindex) ++currentIndex;
        return {cont,skipindex,currentIndex};
    }
    friend bool operator==(const SkipIterator& first, const SkipIterator& second){
        return first.skipindex == second.skipindex && first.currentIndex==second.currentIndex;
    }
    friend bool operator!=(const SkipIterator& first, const SkipIterator& second){
        return !(first.skipindex == second.skipindex && first.currentIndex==second.currentIndex);
    }
    friend bool operator!=(const SkipIterator& first, const ContainerIter& second){
        return !(first.currentIndex == first.cont.size() && first.cont.end()==second);
    }
};
struct SkipContainer{
    using ContType=vector<string>;
    using size_type=ContType::size_type;
    const ContType&  cont;
    ContType::size_type skipindex;
    SkipIterator begin()const{
        if(skipindex==0){
            return {cont,skipindex,1};
        }
        return {cont,skipindex,0};
    }
    auto end()const{
        return cont.end();
    }

};
auto testSkip=[](const vector<string>& v,vector<string>::size_type skipIndex){
    cout<<"words =  {";
    for(auto w:v){
        cout<<w<<",";
    }
    cout<<"}\n";
    cout<<"Skipped words =  {";
    for(auto w:Solution::SkipContainer{v,skipIndex}){
        cout<<w<<",";
    }
    cout<<"}\n";

};

//    testSkip({"word","good","best","third"},0);
//    testSkip({"word","good","best","third"},1);
//    testSkip({"word","good","best","third"},2);
//    testSkip({"word","good","best","third"},3);
//    testSkip({"word","good","best","third"},6);
#endif // SKIPCONTAINER_H
