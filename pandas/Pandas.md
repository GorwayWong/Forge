### Pandas

`iloc` uses the Python stdlib indexing scheme, where the first element of the range is included and the last one excluded. So `0:10` will select entries `0,...,9`. `loc`, meanwhile, indexes inclusively. So `0:10` will select entries `0,...,10`.

读csv： pd.read_csv()

保存为csv： pd.to_csv()

```python
# 查看review表中的country列中是Italy的数据 返回一系列True和False
reviews.country == 'Italy'
# 根据筛选为True的结果来挑选表中数据
reviews.loc[reviews.country == 'Italy']
reviews.loc[(reviews.country == 'Italy') & (reviews.points >= 90)]
```

**isin函数**

```
reviews.loc[reviews.country.isin(['Italy', 'France'])]
```

**isnull&notnull**

```
reviews.loc[reviews.price.notnull()]
```

**注意：iloc和loc后跟的是中括号！不是()**

To combine filtering conditions in Pandas, use bitwise operators ('&' and '|') not pure Python ones ('and' and 'or')

#### Summary functions

```python
reviews.points.describe() # This method generates a high-level summary of the attributes of the given column.
```

#### To see a list of unique values we can use the `unique()` function:

```python
reviews.taster_name.unique()
```

#### To see a list of unique values *and* how often they occur in the dataset, we can use the `value_counts()` method:

```python
reviews.taster_name.value_counts()
```

#### `map()`函数是Pandas中的一个数据处理函数，用于对Series对象（一维数据结构）中的每个元素应用一个函数，返回一个新的Series对象，其中包含经过函数处理后的元素。

```python
review_points_mean = reviews.points.mean()
reviews.points.map(lambda p: p - review_points_mean)
```

#### [`apply()`](https://pandas.pydata.org/pandas-docs/stable/generated/pandas.DataFrame.apply.html) is the equivalent method if we want to transform a whole DataFrame by calling a custom method on each row.

```python
def remean_points(row):
    row.points = row.points - review_points_mean
    return row

reviews.apply(remean_points, axis='columns')
```

Note that `map()` and `apply()` return new, transformed Series and DataFrames, respectively. They don't modify the original data they're called on.

`idxmax()`是Pandas中Series对象的一个方法，用于返回Series中最大值所在的索引位置。

#### groupby

用groupby实现value_counts方法。

```python
reviews.groupby('points').points.count()
```

`groupby('points')`：

- 这一步使用 `groupby()` 方法，按照 'points' 列的不同取值对数据进行分组。
- 意味着将数据集按照葡萄酒得分（'points' 列的值）进行分组。

`.points.count()`：

- 对于每个分组，`.points.count()` 部分执行了计数操作。
- `.points` 选择了 'points' 列，然后 `count()` 统计了该列中每个唯一值的出现次数。

#### reviews.groupby('winery').apply(lambda df: df.title.iloc[0])

1. **`groupby('winery')`:** 这部分代码首先使用 `groupby()` 方法，根据 'winery' 列对 DataFrame 进行分组，将数据按照酿酒厂进行分组。
2. **`apply(lambda df: df.title.iloc[0])`:** 对于每个分组，`apply()` 方法将传递一个 DataFrame，表示该分组的所有行。在这里，使用了一个匿名函数 `lambda`，该函数接受一个 DataFrame (`df`) 并返回该分组中第一行葡萄酒的标题，即 `df.title.iloc[0]`。

#### reviews.groupby(['country','province']).apply(lambda df: df.loc[df.points.idxmax()])

1. **`groupby(['country', 'province'])`:** 这部分代码使用 `groupby()` 方法，根据 'country' 和 'province' 两列对 DataFrame 进行分组，创建了一个多层次的索引。
2. **`apply(lambda df: df.loc[df.points.idxmax()])`:** 对于每个分组，`apply()` 方法将传递一个 DataFrame，表示该分组的所有行。在这里，使用了一个匿名函数 `lambda`。在这个函数中，`df.points.idxmax()` 返回了当前分组中评分最高的葡萄酒的索引。然后，`df.loc[df.points.idxmax()]` 选择了这个具有最高评分的葡萄酒的所有列。

#### reviews.groupby(['country']).price.agg([len, min, max])

1. **`groupby(['country'])`:** 这部分代码使用 `groupby()` 方法，根据 'country' 列对 DataFrame 进行分组，创建了一个多层次的索引。
2. **`.price.agg([len, min, max])`:** 对于每个分组，`agg()` 方法用于进行聚合计算。在这里，对 'price' 列进行了三种不同的聚合操作：`len` 统计每个组中的数据数量，`min` 统计每个组中 'price' 列的最小值，`max` 统计每个组中 'price' 列的最大值。

#### To get data in the order want it in we can sort it ourselves. The `sort_values()` method is handy for this.

```python
countries_reviewed = reviews.groupby(['country', 'province']).description.agg([len])
countries_reviewed = countries_reviewed.reset_index()
countries_reviewed.sort_values(by='len',ascending=False)
```

#### countries_reviewed.sort_values(by=['country','len])

这部分代码调用了 DataFrame 的 `sort_values()` 方法，通过指定 `by` 参数来指定排序的列，其中 `['country', 'len']` 表示先按照 'country' 列进行升序排序，然后在每个国家内部，按照 'len' 列进行升序排序。

The data type for a column in a DataFrame or a Series is known as the **dtype**.

```python
reviews.dtype
```

#### 缺失值

```python
reviews[pd.isnull(reviews.country)]
```

#### 合并数据表

```python
powerlifting_meets.set_index("MeetID").join(powerlifting_competitors.set_index("MeetID"))
```

`set_index` 的目的是将指定的列（在这里是 "MeetID"）设置为新的索引，这样可以在连接/join 操作时以指定的列为准进行匹配。在这个例子中，使用了 `set_index("MeetID")`，将 "MeetID" 列设置为索引，然后通过 `join` 将两个数据框按照相同的索引（"MeetID"）进行连接。